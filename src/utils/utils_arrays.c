/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:21:43 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/04 22:54:48 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(int i, char **array)
{
	while (i > 0)
	{
		i--;
		free(*(array + i));
	}
	free(array);
}

static int	env_list_len(t_env **env_list)
{
	t_env	*current;
	int		len;

	if (!*env_list)
		return (0);
	else
	{
		current = *env_list;
		len = 1;
		while (current->next)
		{
			current = current->next;
			len++;
		}
		return (len);
	}
}

static char	**list_to_array_keys(t_env **env_list, char **array)
{
	int		i;
	t_env	*current;

	if (!*env_list)
	{
		free(array);
		return (NULL);
	}
	current = *env_list;
	i = 0;
	while (current->next)
	{
		*(array + i) = ft_strdup(current->key);
		if (!*(array + i))
		{
			free_array(i, array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	*(array + i++) = ft_strdup(current->key);
	*(array + i) = NULL;
	return (array);
}

static char	**list_to_array_full(t_env **env_list, char **array)
{
	int		i;
	t_env	*current;

	if (!*env_list)
	{
		free(array);
		return (NULL);
	}
	current = *env_list;
	i = 0;
	while (current->next)
	{
		*(array + i) = ft_strdup(current->key);
		if (!*(array + i))
		{
			free_array(i, array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	*(array + i++) = ft_strjoin(current->key, ft_strjoin("=", current->key));
	*(array + i) = NULL;
	return (array);
}

char	**list_to_array(t_env *env_list, int full)
{
	char	**array;
	size_t	len;

	len = env_list_len(&env_list);
	array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	if (full == 1)
		array = list_to_array_full(&env_list, array);
	else
		array = list_to_array_keys(&env_list, array);
	return (array);
}
