# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 12:21:24 by sarherna          #+#    #+#              #
#    Updated: 2024/12/04 23:58:07 by akacprzy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = 	ft_strlen.c ft_strcmp.c ft_strdup.c ft_substr.c ft_strchr.c \
		ft_itoa.c ft_atoi.c ft_memset.c ft_putendl_fd.c ft_putstr_fd.c \
		ft_isalnum.c ft_isdigit.c ft_split.c ft_strjoin.c ft_strisnum.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

# Build library
$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

# Compile each .c file into a .o file
%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
