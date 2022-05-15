/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:39:04 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/15 12:08:45 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simple_minitalk.h"

int	minitalk_atoi(char *str, t_int8 *valid_flag)
{
	unsigned long	num;

	num = 0;
	if (*str == '+')
		str++;
	if (*str < '0' || *str > '9')
		*valid_flag = 0;
	while (*str >= '0' && *str <= '9' && *valid_flag)
	{
		num = num * 10 + *str - '0';
		if (num >> 31)
			*valid_flag = 0;
		str++;
	}
	if (*str)
		*valid_flag = 0;
	return (num);
}

// little endian
void	send_char(int pid, t_uint8 c)
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
		usleep(200);
	}
}

// big endian
void	send_char2(int pid, t_uint8 c)
{
	int	bit_count;

	bit_count = 8;
	while (--bit_count >= 0)
	{
		if ((c >> bit_count) & 1u)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(200);
	}
}

int	main(int argv, char **argc)
{
	int					pid;
	t_int8				valid_pid;

	if (argv != 3)
		return (ft_printf("please input 2 arguments on excution\n\t\
Eg: ./client 1234 \"put message here\"\n"));
	valid_pid = 1;
	pid = minitalk_atoi(argc[1], &valid_pid);
	if (!valid_pid || kill(pid, 0) == -1)
	{
		if (!valid_pid)
			ft_printf("The argument \"%s\" is not an intger pid\n", argc[1]);
		else
			ft_printf("Process \"%d\" does not exist", pid);
		return (0);
	}
	while (*(argc[2]))
	{
		send_char2(pid, *(argc[2]));
		++(argc[2]);
	}
	send_char(pid, '\0');
	return (0);
}
