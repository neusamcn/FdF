# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/14 11:42:58 by ncruz-ne          #+#    #+#              #
#    Updated: 2026/01/17 00:08:33 by ncruz-ne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
HEADER = include/fdf.h

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = libs/minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iinclude -I$(LIBFT_DIR) -I$(MLX_DIR) -O3
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

SRC_DIR = src
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/map_parse.c

OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))


all: $(LIBFT) $(MLX) $(OBJ_DIR) $(NAME)
	@echo "\nFdF is ready.\n"

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $@
	@echo "\n$@ compiled.\n"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) libft.a
	@echo "\n$(LIBFT) compiled.\n"

$(MLX):
	@if [ ! -d $(MLX_DIR) ]; then \
		cd libs && git clone https://github.com/42paris/minilibx-linux.git; \
	fi
	@cd $(MLX_DIR) && ./configure
	@echo "\n$(MLX) compiled.\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\n$@ created.\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "\n$(OBJ_DIR) directory created.\n"


clean:
	@-rm -f $(OBJ)
	@-rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "\nAll object files and libraries removed.\n"

fclean: clean
	@-rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(MLX)
	@echo "\nExecutables, object files and libraries removed.\n"

re: fclean all
	@$(MAKE) -C $(MLX_DIR) re


# Debugger:
MAP_NAME = file.fdf

debug: $(NAME)
	@valgrind --log-file=valgrind_log.log --leak-check=full \
	--show-leak-kinds=all --track-origins=yes -s ./$(NAME) " $(MAP_NAME) "

# readme:
# 	@curl -sS -o README.md \
# 	https://raw.githubusercontent.com/neusamcn/FdF/refs/heads/main/README.md
# 	@echo "\nREADME.md downloaded.\n"


.PHONY: all clean fclean re debug # readme