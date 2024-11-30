/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:37:19 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/28 02:43:01 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*copy_environment(char **envp)
{
	t_env	*env_list;
	int		i;
	t_env	*new_node;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = parse_env_var(envp[i]);
		add_env_node(&env_list, new_node);
		i++;
	}
	return (env_list);
}

char	*get_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(char *key, char *value, t_env **env)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_node = create_env_node(key, value);
	add_env_node(env, new_node);
}

void	free_env_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	unset_env_value(char *key, t_env *env)
{
	t_env	*temp;
	t_env	*current;

	if (ft_strcmp(env->key, key) == 0)
	{
		temp = env;
		env = env->next;
		free_env_node(temp);
	}
	else
	{
		current = env;
		while (current->next != NULL)
		{
			if (ft_strcmp(current->next->key, key) == 0)
			{
				temp = current->next;
				current->next = current->next->next;
				free_env_node(temp);
				break ;
			}
			else
				current = current->next;
		}
	}
}
