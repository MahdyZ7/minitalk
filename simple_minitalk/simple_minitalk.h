/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_minitalk.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 08:37:35 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/15 12:40:52 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLE_MINITALK_H
# define SIMPLE_MINITALK_H

# include <signal.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# ifndef T_UINT8
#  define T_UINT8

typedef unsigned char	t_uint8;

# endif

# ifndef T_INT8
#  define T_INT8

typedef char			t_int8;

# endif

#endif