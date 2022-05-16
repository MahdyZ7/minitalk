# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 12:46:30 by ayassin           #+#    #+#              #
#    Updated: 2022/05/16 11:20:58 by ayassin          ###   ########.fr        #
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

$(NAME):$(OBJS) $(SERVER) $(CLIENT)

$(SERVER): $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) --directory=$$dir; \
    done
	$(CC) $(CFALGS) $(LINKS) server.c -o server
	
$(CLIENT): $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) --directory=$$dir; \
    done
	$(CC) $(CFLAGS) $(LINKS) client.c -o client

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