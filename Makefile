# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/14 11:42:58 by ncruz-ne          #+#    #+#              #
#    Updated: 2026/01/15 00:13:41 by ncruz-ne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
HEADER = include/fdf.h

LIBFT = libs/libft/libft.a #review
MLX = libs/minilibx-linux/libmlx_Linux.a #review

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iinclude -Ilibs/libft -I$(MLX) # -D_DEFAULT_SOURCE # review
LIBFT_FLAGS = -Llibft -lft #review
MLX_FLAGS = -L$(MLX) -lmlx_Linux -lX11 -lXext #review

SRC_DIR = src
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/

OBJ_DIR = obj
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))


all: $(LIBFT) $(MLX) $(OBJ_DIR) $(NAME)
	@echo "Wireframe model is ready."

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $@
	@echo "$@ compiled.\n"

$(LIBFT):
	@$(MAKE) -C libft libft.a
	@echo "$(LIBFT) compiled.\n"

$(MLX):
# 	@$(MAKE) -C
	@echo "$(MLX) compiled.\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$@ created.\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(OBJ_DIR) directory created.\n"


clean:
	@-rm -f $(OBJ)
	@-rm -rf $(OBJ_DIR)
# 	@$(MAKE) -C libft clean
# 	@$(MAKE) -C mlx fclean
	@echo "All object files and libraries removed.\n"

fclean: clean
	@-rm -f $(NAME)
# 	@$(MAKE) -C libft fclean
# 	@$(MAKE) -C mlx fclean
	@echo "Executables, object files and libraries removed.\n"

re: fclean all

readme:
	@curl -sS -o README.md \
	https://raw.githubusercontent.com/neusamcn/minitalk/refs/heads/main/README.md
	@echo "\nREADME.md downloaded.\n"


.PHONY: all clean fclean re readme

