/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:16:34 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/04 02:11:02 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_validate_arg(const char *str)
{
	int		i;

	i = 0;
	if (ft_isdigit(str[0]) == 1)
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
			return (-1);
		i++;
	}
	if (str[i] != '=')
		return (2);
	return (1);
}

static int	print_export_error(int err_no, char *arg)
{
	if (err_no == 0 || err_no == -3 || err_no == -1)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FD);
		ft_putstr_fd(arg, STDERR_FD);
		ft_putendl_fd("\': not a valid identifier: ", STDERR_FD);
	}
	return (ERROR);
}

int	bin_export(char **args, t_env *env)
{
	int		i;
	int		error_ret;
	int		ret;
	t_env	*new_node;

	i = 1;
	ret = SUCCESS;
	if (!args[1])
		env_export_print(env);
	else
	{
		while (args[i])
		{
			error_ret = export_validate_arg(args[i]);
			if (args[i][0] == '=')
				error_ret = -3;
			if (error_ret <= 0)
				ret = print_export_error(error_ret, args[i]);
			else
			{
				new_node = parse_env_var(args[i]);
				add_env_node(&env, new_node);
			}
			i++;
		}
	}
	return (ret);
}
