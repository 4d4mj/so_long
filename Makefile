# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 02:28:08 by ajabado           #+#    #+#              #
#    Updated: 2024/07/14 15:24:02 by ajabado          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# color codes
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m
HIDE	= \033[?25l
SHOW	= \033[?25h
BOLD	= \033[1m

# map
OBJS_MAP = $(SRC_MAP:.c=.o)
SRC_MAP = $(addprefix $(SRC_DIR)/map/, \
algorithms.c map_validator.c read_map.c \
)

# move
OBJS_MOVE = $(SRC_MOVE:.c=.o)
SRC_MOVE = $(addprefix $(SRC_DIR)/move/, \
move_enemies.c move_player.c strategy.c \
)

# render
OBJS_RENDER = $(SRC_RENDER:.c=.o)
SRC_RENDER = $(addprefix $(SRC_DIR)/render/, \
animate.c binary_wall_map.c destroy.c image.c load_sprites.c render_walls.c render.c \
)

# utils
OBJS_UTILS = $(SRC_UTILS:.c=.o)
SRC_UTILS = $(addprefix $(SRC_DIR)/utils/, \
init.c utils.c utils2.c \
)

# so_long
OBJS_SO_LONG = $(SRC_SO_LONG:.c=.o)
SRC_SO_LONG = $(addprefix $(SRC_DIR)/, \
main.c \
)

CC = cc
RM = rm -rf
AR = ar -rcs
CFLAGS	= -Wall -Wextra -Werror -I $(INC_DIR)
MK		= --no-print-directory

NAME = so_long
MLX = mlx/libmlx_linux.a
MLX_FLAGS	= -L ./mlx -lmlx -Ilmlx -lXext -lX11 -lm
LIBFT	= $(LIBFT_PATH)/libft.a

SRCS = $(SRC_MAP) $(SRC_MOVE) $(SRC_RENDER) $(SRC_UTILS) $(SRC_SO_LONG)
INC_DIR			= includes
HEADER			= $(INC_DIR)/so_long.h
SRC_DIR			= srcs
LIBFT_PATH		= libft
MLX_PATH 		= mlx
OBJS = $(OBJS_MAP) $(OBJS_MOVE) $(OBJS_RENDER) $(OBJS_UTILS) $(OBJS_SO_LONG)

COUNTER = 0
TOTAL_FILES = $(words $(SRCS))

all: $(MLX) $(LIBFT) $(NAME) $(HEADER)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(BOLD)${GREEN}> Compiled $(NAME) successfully$(RESET)"

$(LIBFT):
	@make $(MK) -C $(LIBFT_PATH)

$(MLX):
	@echo "$(HIDE)$(BOLD)$(CYAN)Compiling $(MLX_PATH)...$(RESET)"
	@make $(MK) -C $(MLX_PATH)
	@echo "$(SHOW)$(BOLD)$(GREEN)> Compiled $(MLX_PATH) successfully$(RESET)"

%.o : %.c $(HEADER)
	@$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
	@printf "$(HIDE)$(BOLD)$(YELLOW)\rCompiling $(NAME): $(RESET)["
	@printf "%0.s#" $(shell seq 1 $(COUNTER))
	@if [ $(COUNTER) -lt $(TOTAL_FILES) ]; then \
		printf "%0.s." $(shell seq 1 $$(($(TOTAL_FILES) - $(COUNTER)))); \
	fi
	@printf "] (%d/%d)" $(COUNTER) $(TOTAL_FILES)
	@if [ $(COUNTER) -eq $(TOTAL_FILES) ]; then \
		printf "\n$(SHOW)"; \
	fi

clean:
	@make clean $(MK) -C $(LIBFT_PATH)
	@make clean $(MK) -C $(MLX_PATH)
	@$(RM) $(OBJS)
	@echo "$(YELLOW)> ALL object files of $(NAME) have been deleted$(RESET)"

fclean:
	@make fclean $(MK) -C $(LIBFT_PATH)
	@$(RM) $(OBJS)
	@echo "$(YELLOW)> ALL object files of $(NAME) have been deleted$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)> $(NAME) has been deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re
