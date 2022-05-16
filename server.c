/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:49:08 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/16 11:21:45 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_lstpop(t_list **lst);
static int	add_bit4(int signum);
static int	new_client(int sender_pid, t_list **client_queue);
static void	server_hq(int signum, siginfo_t *info, void *ptr);
int			main(void);

/*pop the first node out int the list "*lst" and frees it*/
static void	ft_lstpop(t_list **lst)
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

/* recive bits and order them into a char big endian style
writes the char every 8 bits
Returns 1 whan a null char is made (signals end of transmition)*/
static int	add_bit4(int signum)
{
	static char	c;
	static int	bit_count;

	if (signum == MINITALK_INIT)
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
		return (add_bit4(MINITALK_INIT) + 1);
	}
	return (add_bit4(MINITALK_INIT));
}

/* add a new process with id "sender_pid to the client queue as a node
if the added node is the first send a message back and start transmition*/
static int	new_client(int sender_pid, t_list **client_queue)
{
	int		*pid;
	t_list	*temp_node;

	pid = (int *)malloc(sizeof(*pid));
	if (pid == NULL)
		return (kill(*pid, SIGUSR1));
	*pid = sender_pid;
	temp_node = ft_lstnew(pid);
	if (temp_node == NULL)
	{
		free(pid);
		return (kill(*pid, SIGUSR1));
	}
	ft_lstadd_back(client_queue, temp_node);
	if (sender_pid == *((int *)(*client_queue)->content))
	{
		if (kill(*pid, SIGUSR2) == -1)
			ft_lstpop(client_queue);
	}
	return (0);
}

/* switch function to handle SIGUSR1, SIGUSR2, and SIGINT signals
- SIGINT: clear queue and exit
- MINITALK_INT: intilize the queue to NULL if info is NULL
_______________ Go through the list in order and intiate contact 
_______________ with the first pid that responds
- SIGUSR1 || SIGUSR2 : add the pid of the sender to the queue
______________________ if the signal is from the fist node in the queue
______________________ start printing the message
______________________ if a null is  recived intiate contact with the 
______________________ next item in the queue
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
	else if (signum == MINITALK_INIT && info != NULL)
		while (client_queue
			&& kill(*(int *)client_queue->content, SIGUSR2) == -1)
			ft_lstpop(&client_queue);
	else if (signum == MINITALK_INIT && info == NULL)
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

/* set up the signal handlers and start an infinate loop*/
int	main(void)
{
	struct sigaction	sa;

	add_bit4(MINITALK_INIT);
	server_hq(MINITALK_INIT, NULL, NULL);
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
