/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:49:08 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/15 17:02:12 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_minitalk.h"

t_uint8	g_bit_count;

// small endian bit transfer
void	add_bit(int signum)
{
	static char	c;

	if (signum == SIGUSR2)
		c = c | (1u << g_bit_count);
	++g_bit_count;
	if (g_bit_count == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
			write(1, "\n", 1);
		g_bit_count = 0;
		c = c & 0;
	}
}

// big endian bit transfer
void	add_bit2(int signum)
{
	static char	c;

	c <<= 1;
	if (signum == SIGUSR2)
		c |= 1u;
	++g_bit_count;
	if (g_bit_count == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
			write(1, "\n", 1);
		g_bit_count = 0;
		c = c & 0;
	}
}

int	main(void)
{
	g_bit_count = 0;
	ft_printf("the process id is %d\n", getpid());
	signal(SIGUSR1, add_bit2);
	signal(SIGUSR2, add_bit2);
	while (1)
		;
	return (0);
}

// void	server_hq(int signum, siginfo_t *info, void *ptr)
// {
// 	static t_list	*client_queue;
	
// 	if (signum == 0)
// 		kill(info->si_pid, SIGUSR2);
// 	else if (client_queue == NULL || info->si_pid != *((int *)client_queue->content))
// 		new_client(info->si_pid, &client_queue);
// 	else if (client_queue && info->si_pid == *((int *)client_queue->content))
// 	{
// 		if (add_bit4(signum))
// 		{
// 			ft_lstpop(&client_queue);
// 			if (client_queue)
// 			{
// 				info->si_pid = *((int *)client_queue->content);
// 				server_hq(0, info, ptr);
// 			}
// 		}
// 	}
// }
