# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 12:46:30 by ayassin           #+#    #+#              #
#    Updated: 2022/05/10 15:10:21 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SERVER = server

CLIENT = client

HEADER = minitalk.h

SRC = server.c client.c

SUBDIRS = libft ft_printf

CC = gcc

CFLAGS = -Werror -Wall -Wextra

LINKS = -Llibft -lft -Lft_printf -lftprintf

OBJS = $(SRC:.c=.o)

all: $(CLIENT) $(SERVER)

.c.o:
	$(CC) $(CFALGS) -c $^ -o $@

$(NAME):$(OBJS) $(SERVER $(CLIENT))

$(SERVER):
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFALGS) -c server.c
	$(CC) $(CFALGS) $(LINKS) server.c -o server
	
$(CLIENT):
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFALGS) -c client.c
	$(CC) $(CFLAGS) $(LINKS) client.c -o client

clean:
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
    done
	rm -f $(OBJS)
	

fclean: clean
	@for dir in $(SUBDIRS); do \
        $(MAKE) fclean -C $$dir; \
    done
	rm -f $(NAME) $(SERVER) $(CLIENT)

re : fclean all

.PHONY: clean fclean all re