# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 10:30:26 by trpham            #+#    #+#              #
#    Updated: 2025/03/03 17:26:52 by trpham           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g

SRCS = main.c \
		maps.c \
		maps_helper1.c \
		maps_helper2.c \
		image_render.c \
		player.c

OBJS = $(SRCS:%.c=%.o)

NAME = so_long

LIBFT_DIR = ./libft
LIBFT_NAME = $(LIBFT_DIR)/libft.a

# MLX configuration
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm -lz
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

all: check_mlx $(NAME)

# checking whether mlx library has been installed
check_mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "MLX not found, cloning into $(MLX_DIR)"; \
		git clone $(MLX_REPO) mlx; \
		make -C $(MLX_DIR); \
	fi

# Contains the X11 and MLX header files
INCLUDES = -I/usr/include -I$(MLX_DIR) -I$(LIBFT_DIR)

%.o: %.c so_long.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(NAME): $(OBJS) $(LIBFT_NAME) $(MLX_LIB)
	$(CC) $(CFLAGS) $^ -o $@ $(MLX_FLAGS)

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f  $(NAME)

re: fclean all

.PHONY: all clean fclean re

