# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mirokugo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/16 21:57:10 by mirokugo          #+#    #+#              #
#    Updated: 2025/09/16 22:18:47 by mirokugo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = -I./mlx

LIBS = -L./mlx -lmlx -lXext -lX11 -lm -lz

NAME = fractol

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)


