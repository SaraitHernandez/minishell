/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins_echo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:51:30 by akacprzy          #+#    #+#             */
/*   Updated: 2024/11/27 00:32:06 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtin_echo.c"
#include "../../libft/ft_strcmp.c"
#include "../../libft/ft_putstr_fd.c"
#include <stdio.h>

/*
Prepare:
Comment main function in minishell.h
Compile:
cc -Wall -Wextra -Werror src/tests/test_builtins_echo.c -o test_echo.out -I includes -I libft
Test:
run out file with arguments to be printed
*/

int	main(int argc, char **argv)
{
	printf("Arguments provided: %d\n", argc-1);
	bin_echo(argv);
	return 0;
}
