# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 12:46:30 by ayassin           #+#    #+#              #
#    Updated: 2022/05/10 09:00:39 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

HEADER = server.h client.h

SRC = server.c client.c

SUBDIRS = libft ft_printf

CC = gcc

CFLAGS = -Werror -Wall -Wextra

LINKS = -Llibft -lft -Lft_printf -lftprintf

OBJS = $(SRC:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFALGS) -c $^ -o $@

$(NAME): $(SUBDIRS) $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFALGS) $(LINKS) server.c -o server
	$(CC) $(CFLAGS) $(LINKS) client.c -o client

$(SUBDIRS):
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done

clean:
	rm -f $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
    done

fclean: clean
	rm -f $(NAME)
	for dir in $(SUBDIRS); do \
        $(MAKE) fclean -C $$dir; \
    done

re : fclean all

.PHONY: clean fclean all re