/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:39:04 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/12 13:08:29 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// little endian
void	send_char(int pid, uint8_t c)
{
	int	bit_count;

	bit_count = 0;
	while (bit_count < 8)
	{
		if (c & 1u)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c >>= 1;
		++bit_count;
		usleep(250);
	}
}

// big endian
void	send_char2(int pid, uint8_t c)
{
	int	bit_count;

	bit_count = 8;
	while (--bit_count >= 0)
	{
		if ((c >> bit_count) & 1u)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(250);
	}
}

int	main(int argv, char **argc)
{
	int	pid;

	if (argv == 3)
	{
		pid = ft_atoi(argc[1]);
		if (kill(pid, 0) == -1)
		{
			ft_printf("Process \"%d\" does not exist", pid);
			return (0);
		}
		while (*(argc[2]))
		{
			send_char2(pid, *(argc[2]));
			++(argc[2]);
		}
		send_char(pid, '\0');
	}
	return (0);
}
