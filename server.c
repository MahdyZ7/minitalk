/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:49:08 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/14 15:47:04 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

uint8_t	bit_count;

// // small endian bit transfer
// void	add_bit(int signum)
// {
// 	static char	c;

// 	if (signum == SIGUSR2)
// 		c = c | (1u << bit_count);
// 	++bit_count;
// 	if (bit_count == 8)
// 	{
// 		write(1, &c, 1);
// 		if (c == '\0')
// 			write(1, "\n", 1);
// 		bit_count = 0;
// 		c = c & 0;
// 	}
// }

// // big endian bit transfer
// void	add_bit2(int signum)
// {
// 	static char	c;

// 	c <<= 1;
// 	if (signum == SIGUSR2)
// 		c |= 1u;
// 	++bit_count;
// 	if (bit_count == 8)
// 	{
// 		write(1, &c, 1);
// 		if (c == '\0')
// 			write(1, "\n", 1);
// 		bit_count = 0;
// 		c = c & 0;
// 	}
// }

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

	c <<= 1;
	if (signum == SIGUSR2)
		c |= 1u;
	++bit_count;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
		{
			write(1, "\n", 1);
			bit_count = 0;
			c = c & 0;
			return (1);
		}
		bit_count = 0;
		c = c & 0;
	}
	return (0);
}

void	add_bit3(int signum, siginfo_t *info, void *ptr)
{
	static t_list	*signal_queue;
	int				*pid;

	(void) ptr;
	if (signal_queue == NULL)
	{
		pid = (int *)malloc(sizeof(*pid));
		*pid = info->si_pid;
		ft_lstadd_back(&signal_queue, ft_lstnew(pid));
		kill(*pid, SIGUSR2);
		return ;
	}
	else if (signum == 0)
		kill(info->si_pid, SIGUSR2);
	else if (info->si_pid == *((int *)signal_queue->content))
	{
		if (add_bit4(signum))
		{
			ft_lstpop(&signal_queue);
			if (signal_queue)
			{
				info->si_pid = *((int *)signal_queue->content);
				add_bit3(0, info, NULL);
			}
		}
	}
	else
	{
		pid = (int *)malloc(sizeof(*pid));
		*pid = info->si_pid;
		ft_lstadd_back(&signal_queue, ft_lstnew(pid));
	}
}

// int	main2(void)
// {
// 	bit_count = 0;
// 	ft_printf("the process id is %d\n", getpid());
// 	signal(SIGUSR1, add_bit2);
// 	signal(SIGUSR2, add_bit2);
// 	while (1)
// 		;
// 	return (0);
// }

int	main(void)
{
	struct sigaction	sa;

	bit_count = 0;
	ft_printf("the process id is %d\n", getpid());
	//sa.sa_handler = add_bit2;
	sa.sa_sigaction = add_bit3;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction (SIGUSR2, &sa, NULL);
	while (1)
		;
	return (0);
}
