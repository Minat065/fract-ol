# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/16 21:57:10 by mirokugo          #+#    #+#              #
#    Updated: 2025/09/24 20:54:06 by mirokugo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = -I./mlx -I./libft -I./includes

LIBFT = libft/libft.a
LIBS = -L./mlx -lmlx ./libft/libft.a -lXext -lX11 -lm -lz

NAME = fractol

CFLAGS = -Wall -Wextra -Werror

CC = gcc

SRC = srcs/main.c \
	  srcs/init.c \
	  srcs/draw.c \
	  srcs/events.c \
	  srcs/utils.c \
	  srcs/fractals.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re


