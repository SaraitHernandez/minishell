# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 11:39:14 by sarherna          #+#    #+#              #
#    Updated: 2024/11/24 13:13:22 by sarherna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRC_DIR := src
BUILTINS_DIR := $(SRC_DIR)/builtins
ENV_DIR := $(SRC_DIR)/environment
UTILS_DIR := $(SRC_DIR)/utils
INCLUDE_DIR := includes
LIBFT_DIR := libft

SRCS := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init_shell.c \
	$(SRC_DIR)/input.c \
	$(SRC_DIR)/lexer_utils.c \
	$(SRC_DIR)/lexer.c \
	$(SRC_DIR)/expand_variables.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/parser_utils.c \
	$(SRC_DIR)/executor.c \
	$(SRC_DIR)/exec_utils.c \
	$(SRC_DIR)/redirection.c \
	$(SRC_DIR)/pipes.c \
	$(SRC_DIR)/signals.c \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/globals.c \
	$(BUILTINS_DIR)/builtin_echo.c \
	$(BUILTINS_DIR)/builtin_cd.c \
	$(BUILTINS_DIR)/builtin_pwd.c \
	$(BUILTINS_DIR)/builtin_export.c \
	$(BUILTINS_DIR)/builtin_unset.c \
	$(BUILTINS_DIR)/builtin_env.c \
	$(BUILTINS_DIR)/builtin_exit.c \
	$(ENV_DIR)/environment.c \
	$(ENV_DIR)/environment_utils.c \
	$(ENV_DIR)/enviroment_variables.c \
	$(UTILS_DIR)/utils_strings.c \
	$(UTILS_DIR)/utils_memory.c \
	$(UTILS_DIR)/utils_errors.c

OBJS := $(SRCS:.c=.o)

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g
IFLAGS := -I $(INCLUDE_DIR) -I $(LIBFT_DIR)
LDFLAGS := -L $(LIBFT_DIR) -lft -lreadline

RM := rm -f
MKDIR := mkdir -p

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)


re: fclean all


.PHONY: all clean fclean re

debug: CFLAGS += -g -fsanitize=address
debug: re
