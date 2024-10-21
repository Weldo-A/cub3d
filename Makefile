# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abernade <abernade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 17:14:48 by abernade          #+#    #+#              #
#    Updated: 2024/10/21 06:01:26 by abernade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= cub3d

SRC_DIR = srcs

OBJ_DIR = obj

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE_DIR = include

SRC_FILES = main.c \
			cubdata.c \
			debug.c \
			errors.c \
			hooks.c \
			render.c \
			texture_utils.c
			

SRC = $(SRC_FILES:%.c=$(SRC_DIR)/%.c)

#OBJ = $(addsuffix .o,$(basename $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES)))))
OBJ = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

CC = cc

CFLAGS = -ldl -lglfw -pthread -lm -Wall -Wextra -Werror -g

MLX_DIR = MLX42

MLX = $(MLX_DIR)/build/libmlx42.a

MLX_INCLUDE = $(MLX_DIR)/include/MLX42

INCLUDE = -I/usr/include/X11 \
			-I$(MLX_INCLUDE) \
			-I$(INCLUDE_DIR) \
			-I$(LIBFT_DIR)/include

VPATH = srcs

define compile-obj
$(CC) $(CFLAGS) $(INCLUDE) -O3 -c $< -o $@
endef

all: $(NAME)

$(MLX):
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(compile-obj)

$(NAME): $(MLX) $(OBJ)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) -lm -lz $(INCLUDE) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	rm -rf $(MLX_DIR)/build

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re