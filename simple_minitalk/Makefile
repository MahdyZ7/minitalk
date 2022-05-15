# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 12:46:30 by ayassin           #+#    #+#              #
#    Updated: 2022/05/15 11:34:41 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = simple_minitalk

SERVER = simple_server

CLIENT = simple_client

HEADER = simple_minitalk.h

SRC = simple_server.c simple_client.c

SUBDIRS = libft ft_printf

CC = gcc

CFLAGS = -Werror -Wall -Wextra

LINKS = -Llibft -lft -Lft_printf -lftprintf

OBJS = $(SRC:.c=.o)

all: $(CLIENT) $(SERVER)

.c.o:
	$(CC) $(CFALGS) -c $^ -o $@

$(NAME):$(OBJS) $(SERVER) $(CLIENT)

$(SERVER): $(OBJS) 
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFALGS) $(LINKS) simple_server.c -o simple_server
	
$(CLIENT): $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFLAGS) $(LINKS) simple_client.c -o simple_client

clean:
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
    done
	rm -f $(OBJS) 
	

fclean: clean
	for dir in $(SUBDIRS); do \
        $(MAKE) fclean -C $$dir; \
    done
	rm -f $(NAME) $(SERVER) $(CLIENT)

re : fclean all

.PHONY: clean fclean all re