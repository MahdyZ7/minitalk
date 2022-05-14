/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:39:04 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/14 23:21:44 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	pid;

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
uint8_t	ft_isint(char *str)
{
	return (*str);
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

void	add_bit3(int signum, siginfo_t *info, void *ptr)
{
	//if (info->si_pid == pid)
	(void) signum;
	(void) info;
	(void) ptr;
	ft_printf("It is happning\n");
}

int	main(int argv, char **argc)
{
	int	pid;
	struct sigaction	sa;
	
	sa.sa_sigaction = add_bit3;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR2, &sa, NULL);
	if (argv == 3)
	{
		pid = ft_atoi(argc[1]);
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_printf("Process \"%d\" does not exist", pid);
			return (0);
		}
		else
			pause();
		while (*(argc[2]))
		{
			send_char2(pid, *(argc[2]));
			++(argc[2]);
		}
		send_char(pid, '\0');
	}
	return (0);
}
	