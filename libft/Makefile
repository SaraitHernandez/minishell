# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 12:21:24 by sarherna          #+#    #+#              #
#    Updated: 2024/11/16 15:53:00 by sarherna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = 	ft_strlen.c ft_strcmp.c ft_strdup.c ft_substr.c ft_strchr.c \
		ft_itoa.c ft_atoi.c
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
