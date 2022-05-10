/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:39:04 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/10 15:22:54 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sighandler(int bit)
{
	
}

int	main(int argv, char **argc)
{
	if (argv == 3)
		signal(SIGINT, sighandler);
	return (0);
}
