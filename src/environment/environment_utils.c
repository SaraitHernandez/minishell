/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:27:17 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 11:28:29 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit_with_error("Memory allocation failed");
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	add_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*current;

	if (!*env_list)
		*env_list = new_node;
	else
	{
		current = *env_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

char	**env_list_to_array(t_env *env)
{
	(void)env;
	return (NULL);
}

t_env	*parse_env_var(char *env_var)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*new_node;

	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		key = ft_substr(env_var, 0, equal_sign - env_var);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = ft_strdup(env_var);
		value = ft_strdup("");
	}
	new_node = create_env_node(key, value);
	free(key);
	free(value);
	return (new_node);
}
