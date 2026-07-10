# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: makoon <makoon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 20:37:03 by makoon            #+#    #+#              #
#    Updated: 2025/04/11 16:45:45 by makoon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

SRC = ./main.c \
	  ./init.c \
	  ./parsing.c \
	  ./routine.c \
	  ./thread.c \
	  ./utils.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -g3 -Wall -Werror -Wextra -pthread -I ./includes/

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re