/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:16:34 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/08 17:00:12 by akacprzy         ###   ########.fr       */
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
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
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
		ft_putendl_fd("\': not a valid identifier", STDERR_FD);
	}
	return (ERROR);
}

static void	export_arg_to_env(char *arg, t_env *env)
{
	t_env	*new_node;

	new_node = parse_env_var(arg);
	unset_env_value(new_node->key, env);
	add_env_node(&env, new_node);
}

void	bin_export(char **args, t_shell *shell)
{
	int		i;
	int		error_type;

	i = 1;
	shell->exit_status = 0;
	if (!args[1] || args[1][0] == '\0')
		env_export_print(shell->env_list);
	else
	{
		while (args[i])
		{
			error_type = export_validate_arg(args[i]);
			if (args[i][0] == '=')
				error_type = -3;
			if (error_type <= 0)
				shell->exit_status = print_export_error(error_type, args[i]);
			else
			{
				export_arg_to_env(args[i], shell->env_list);
				shell->exit_status = 0;
			}
			i++;
		}
	}
}
