/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:49:08 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/15 17:46:55 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*pop the first item out int the list "*lst" and frees it*/
void	ft_lstpop(t_list **lst)
{
	t_list	*temp;

	if (!lst)
		return ;
	if (!*lst)
		return ;
	temp = *lst;
	*lst = (*lst)->next;
	ft_lstdelone(temp, free);
}

// big endian bit transfer
int	add_bit4(int signum)
{
	static char	c;
	static int	bit_count;

	if (signum == MINITALK_INT)
	{
		c = 0;
		bit_count = 0;
		return (0);
	}
	++bit_count;
	c <<= 1;
	if (signum == SIGUSR2)
		c |= 1u;
	if (bit_count != 8)
		return (0);
	if (c != '\0')
		write(1, &c, 1);
	else
	{
		write(1, "\n", 1);
		return (add_bit4(MINITALK_INT) + 1);
	}
	return (add_bit4(MINITALK_INT));
}

/* add an new process with id "sender_pid to the client queue*/
int	new_client(int sender_pid, t_list **client_queue)
{
	int		*pid;
	t_list	*temp;

	pid = (int *)malloc(sizeof(*pid));
	if (pid == NULL)
		return (kill(*pid, SIGUSR1));
	*pid = sender_pid;
	temp = ft_lstnew(pid);
	if (temp == NULL)
	{
		free(pid);
		return (kill(*pid, SIGUSR1));
	}
	ft_lstadd_back(client_queue, temp);
	if (sender_pid == *((int *)(*client_queue)->content))
		return (kill(*pid, SIGUSR2));
	return (0);
}

/* switch function to handle SIGUSR1, SIGUSR2, and SIGINT signals
*/
static void	server_hq(int signum, siginfo_t *info, void *ptr)
{
	static t_list	*client_queue;

	if (signum == SIGINT)
	{
		ft_lstclear(&client_queue, free);
		write(1, "\n", 1);
		exit(0);
	}
	else if (signum == MINITALK_INT && info != NULL)
		while (client_queue
			&& kill(*(int *)client_queue->content, SIGUSR2) == -1)
			ft_lstpop(&client_queue);
	else if (signum == MINITALK_INT && info == NULL)
		client_queue = NULL;
	else if (client_queue == NULL
		|| info->si_pid != *((int *)client_queue->content))
		new_client(info->si_pid, &client_queue);
	else if (client_queue && info->si_pid == *((int *)client_queue->content))
	{
		if (add_bit4(signum) == 0)
			return ;
		ft_lstpop(&client_queue);
		server_hq(0, info, ptr);
	}
}

int	main(void)
{
	struct sigaction	sa;

	add_bit4(MINITALK_INT);
	server_hq(MINITALK_INT, NULL, NULL);
	ft_printf("the process id is %d\n", getpid());
	sa.sa_sigaction = server_hq;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	while (1)
		;
	return (0);
}
