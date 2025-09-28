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

INCLUDES = -I./mlx

LIBS = -L./mlx -lmlx -lXext -lX11 -lm -lz

NAME = fractol

CFLAGS = -Wall -Wextra -Werror

CC = gcc

SRC = srcs/main.c \
	  mandelbrot.c \
	  julia.c \
	  burning_ship.c \
	  utils.c \
	  hooks.c \
	  colors.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)


