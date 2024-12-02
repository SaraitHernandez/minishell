/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:27:17 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/01 14:58:13 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_array_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static void	env_export_sort(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void	env_export_print(t_env *env)
{
	int		i;
	int		len;
	char	**arr;

	arr = list_to_array(env, 0);
	len = env_array_len(arr);
	env_export_sort(arr, len);
	i = 0;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(get_env_value(arr[i], env), 1);
		ft_putendl_fd("\"", 1);
		i++;
	}
	free_array(len, arr);
}
