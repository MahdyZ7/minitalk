/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:49:08 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/12 15:28:46 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

uint8_t	bit_count;

// small endian bit transfer
void	add_bit(int x)
{
	static char	c;

	if (x == SIGUSR2)
		c = c | (1u << bit_count);
	else if (x == SIGUSR1)
		c = c;
	++bit_count;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
			write(1, "\n", 1);
		bit_count = 0;
		c = c & 0;
	}
}

// big endian bit transfer
void	add_bit2(int x)
{
	static char	c;

	c <<= 1;
	if (x == SIGUSR2)
		c |= 1u;
	++bit_count;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
			write(1, "\n", 1);
		bit_count = 0;
		c = c & 0;
	}
}

// void	add_two(int signum, siginfo_t *info, void *ptr)
// {
// 	if (signum == SIGUSR2)
// 		write(1, "1", 1);
// 	else if (signum == SIGUSR1)
// 		write(1, "0", 1);
// 	++bit_count;
// 	if (bit_count == 8)
// 	{
// 		write(1, "\n", 1);
// 		bit_count = 0;
// 		exit(0);
// 	}
// }

int	main(void)
{
	bit_count = 0;
	write(1, "green\n", 7);
	ft_printf("the process id is %d\n", getpid());
	signal(SIGUSR1, add_bit2);
	signal(SIGUSR2, add_bit2);
	while (1)
		;
	return (0);
}
