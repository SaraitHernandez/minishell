# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 11:39:14 by sarherna          #+#    #+#              #
#    Updated: 2024/12/02 22:10:31 by akacprzy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SRC_DIR := src
BUILTINS_DIR := $(SRC_DIR)/builtins
ENV_DIR := $(SRC_DIR)/environment
UTILS_DIR := $(SRC_DIR)/utils
TESTS_DIR := $(SRC_DIR)/tests
INCLUDE_DIR := includes
LIBFT_DIR := libft

SRCS := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/main_utils.c \
	$(SRC_DIR)/init_shell.c \
	$(SRC_DIR)/input.c \
	$(SRC_DIR)/lexer_utils.c \
	$(SRC_DIR)/lexer.c \
	$(SRC_DIR)/expand_variables.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/parser_utils.c \
	$(SRC_DIR)/parser_nodes.c \
	$(SRC_DIR)/executor.c \
	$(SRC_DIR)/exec_utils.c \
	$(SRC_DIR)/exec_redirs.c \
	$(SRC_DIR)/exec_pipes.c \
	$(SRC_DIR)/exec_builtins.c \
	$(SRC_DIR)/redirection.c \
	$(SRC_DIR)/heredoc.c \
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
	$(ENV_DIR)/environment_variables.c \
	$(ENV_DIR)/environment_export.c \
	$(UTILS_DIR)/utils_arrays.c \
	$(UTILS_DIR)/utils_strings.c \
	$(UTILS_DIR)/utils_memory.c \
	$(UTILS_DIR)/utils_errors.c \
	$(TESTS_DIR)/tests_parser.c \
	$(TESTS_DIR)/tests_parser_utils.c \


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
