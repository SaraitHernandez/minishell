/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins_pwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:51:30 by akacprzy          #+#    #+#             */
/*   Updated: 2024/11/26 22:41:29 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtin_pwd.c"
#include "../../libft/ft_putendl_fd.c"
#include <stdio.h>

/*
Prepare:
Comment main function in minishell.h
Compile:
cc -Wall -Wextra -Werror src/tests/test_builtins_pwd.c -o test_pwd.out -I includes -I libft
Test:
run out file from different locations, it should print current working directory and return code
*/

int	main(void)
{
	printf("Return Code: %d\n", bin_pwd());
	return 0;
}
