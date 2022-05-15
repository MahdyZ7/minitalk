/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:39:04 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/15 16:58:32 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	minitalk_atoi(char *str, t_uint8 *valid_flag)
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
		usleep(WAIT_BUFFER);
	}
}

void	client_wait(int signum, siginfo_t *info, void *ptr)
{
	static int	pid;

	if (info == NULL && ptr == NULL)
	{
		pid = signum;
		ft_printf("waiting for server \"%d\"\n", pid);
		kill(pid, SIGUSR2);
		pause();
	}
	else if (info->si_pid == pid)
	{
		if (signum == SIGUSR2)
		{
			ft_printf("Sending messsage ...\n", pid);
			pid = 0;
		}
		else if (signum == SIGUSR1)
		{
			ft_printf("failed to deliver message\n");
			exit(0);
		}
	}
}

void	send_string(int pid, char *message)
{
	char	chars_sent;

	chars_sent = 0;
	client_wait(pid, NULL, NULL);
	while (*message)
	{
		send_char2(pid, *message);
		++chars_sent;
		if (chars_sent == 0)
			usleep(WAIT_BUFFER);
		++message;
	}
	send_char2(pid, '\0');
	ft_printf("message sent\n");
}

int	main(int argv, char **argc)
{
	int					pid;
	t_uint8				valid_pid;
	struct sigaction	sa;

	if (argv != 3)
		return (ft_printf("please input 2 arguments on excution\n\t\
Eg: ./client 1234 \"put message here\"\n"));
	valid_pid = 1;
	sa.sa_sigaction = client_wait;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR2, &sa, NULL);
	pid = minitalk_atoi(argc[1], &valid_pid);
	if (!valid_pid)
		return (ft_printf("The second argument \"%s\" is not an intger pid\n",
				argc[1]));
	if (kill(pid, 0) == -1)
		return (ft_printf("Process \"%d\" does not exist\n", pid));
	send_string(pid, argc[2]);
	return (0);
}
