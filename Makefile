# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/16 21:57:10 by mirokugo          #+#    #+#              #
#    Updated: 2025/10/02 00:12:36 by mirokugo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = -I./mlx -I./libft -I./includes
LIBFT = libft/libft.a
LIBS = -L./mlx -lmlx ./libft/libft.a -lXext -lX11 -lm -lz
NAME = fractol
CFLAGS = -Wall -Wextra -Werror
CC = gcc

# Mandatory sources
SRC = srcs/main.c \
	  srcs/init.c \
	  srcs/draw.c \
	  srcs/events.c \
	  srcs/cleanup.c \
	  srcs/utils.c \
	  srcs/fractals.c \
	  srcs/fractals_draw.c \
	  srcs/colors.c \
	  srcs/colors_utils.c \
	  srcs/validation.c

OBJ = $(SRC:.c=.o)

# Bonus sources
SRC_BONUS = srcs/main_bonus.c \
			srcs/init.c \
			srcs/draw_bonus.c \
			srcs/events_bonus.c \
			srcs/events_utils_bonus.c\
			srcs/cleanup.c \
			srcs/utils.c \
			srcs/fractals_bonus.c \
			srcs/fractals_draw_bonus.c \
			srcs/colors.c \
			srcs/colors_utils.c \
			srcs/validation.c

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

bonus: .bonus

.bonus: $(OBJ_BONUS) $(LIBFT)
	$(CC) $(OBJ_BONUS) $(LIBS) -o $(NAME)
	@touch .bonus

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	rm -f .bonus
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
