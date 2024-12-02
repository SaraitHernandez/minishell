/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:29:28 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/02 22:39:10 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tokens(t_token *tokens, t_env *env)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			char *expanded_value = expand_variable(current->value, env);
			free(current->value);
			current->value = expanded_value;
		}
		current = current->next;
	}
}

char	*expand_variable(char *str, t_env *env)
{
	int		i;
	char	*result;
	char	*var_value;
	char	*var_name;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				var_value = ft_itoa(g_exit_status);
				result = ft_strjoin_free(result, var_value);
				free(var_value);
				i += 2;
			}
			else if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
			{
				var_name = get_var_name(&str[i + 1]);
				var_value = get_env_value(var_name, env);
				result = ft_strjoin_free(result, var_value ? var_value : "");
				free(var_name);
				i += ft_strlen(var_name) + 1;
			}
			else
				result = ft_strjoin_char(result, str[i++]);
		}
		else
			result = ft_strjoin_char(result, str[i++]);
	}
	return (result);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_strndup(str, i);
	return (var_name);
}
