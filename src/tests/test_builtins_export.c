/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:51:30 by akacprzy          #+#    #+#             */
/*   Updated: 2024/11/28 01:01:45 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtin_export.c"
#include "../builtins/builtin_env.c"
#include "../environment/environment.c"
#include "../environment/environment_utils.c"
#include "../environment/enviroment_variables.c"
#include "../environment/environment_export.c"
#include "../utils/utils_arrays.c"
#include "../../libft/ft_isalnum.c"
#include "../../libft/ft_isdigit.c"
#include "../../libft/ft_putstr_fd.c"
#include "../../libft/ft_putendl_fd.c"
#include "../../libft/ft_strchr.c"
#include "../../libft/ft_strdup.c"
#include "../../libft/ft_strcmp.c"
#include "../../libft/ft_substr.c"
#include "../../libft/ft_strlen.c"
#include "../utils/utils_errors.c"
#include <stdio.h>

/*
Prepare:
Comment main function in minishell.h
Compile:
cc -Wall -Wextra -Werror src/tests/test_builtins_export.c -o test_export.out -I includes -I libft
Test:
run out file with arguments to be printed
*/

int	main(int argc, char **argv, char **envp)
{
	t_env *env;

	env = copy_environment(envp);
	printf("Arguments provided: %d\n", argc-1);
	printf("Exit Code: %d\n", bin_export(argv, env));

	if (argc > 1)
	{
		bin_env(env);
	}

	free_env_list(env);
	return 0;
}
