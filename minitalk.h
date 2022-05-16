/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:37:35 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/16 09:57:33 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# ifndef T_UINT8
#  define T_UINT8

typedef unsigned char	t_uint8; // dumb typedef of uint8_t for linux
# endif

# define WAIT_BUFFER 300	// wait peroid btween segnals
# define MINITALK_INIT 0		// intilization signal

#endif