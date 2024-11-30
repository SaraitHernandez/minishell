/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:51:30 by akacprzy          #+#    #+#             */
/*   Updated: 2024/11/27 00:33:05 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtin_cd.c"
#include "../builtins/builtin_pwd.c"
#include "../environment/environment.c"
#include "../environment/environment_utils.c"
#include "../environment/enviroment_variables.c"
#include "../../libft/ft_putendl_fd.c"
#include "../../libft/ft_putstr_fd.c"
#include "../../libft/ft_strdup.c"
#include "../../libft/ft_strcmp.c"
#include "../../libft/ft_substr.c"
#include "../../libft/ft_strchr.c"
#include "../../libft/ft_strlen.c"
#include "../utils/utils_errors.c"
#include <stdio.h>

/*
Prepare:
Comment main function in minishell.h
Compile:
cc -Wall -Wextra -Werror src/tests/test_builtins_cd.c -o test_cd.out -I includes -I libft
Test:
run out file providing different paths and check output
*/

int	main(int argc, char **argv, char **envp)
{
	t_env *env;
	char *args2[] = {"bin_cd", '\0'};
	char *args3[] = {"bin_cd", "-", '\0'};

	env = copy_environment(envp);
	printf("Arguments provided: %d\n", argc-1);
	printf("Starting path:\n");
	bin_pwd();
	printf("PWD: %s\n", get_env_value("PWD" ,env));
	printf("OLDPWD: %s\n", get_env_value("OLDPWD" ,env));
	bin_cd(argv, env);
	printf("Provided path:\n");
	bin_pwd();
	printf("PWD: %s\n", get_env_value("PWD" ,env));
	printf("OLDPWD: %s\n", get_env_value("OLDPWD" ,env));
	bin_cd(args2, env);
	printf("Home path:\n");
	bin_pwd();
	printf("PWD: %s\n", get_env_value("PWD" ,env));
	printf("OLDPWD: %s\n", get_env_value("OLDPWD" ,env));
	bin_cd(args3, env);
	printf("Previous (-) path:\n");
	bin_pwd();
	printf("PWD: %s\n", get_env_value("PWD" ,env));
	printf("OLDPWD: %s\n", get_env_value("OLDPWD" ,env));

	free_env_list(env);
	return 0;
}
