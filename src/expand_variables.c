/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:29:28 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 14:15:37 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*current;
	char	*expanded_value;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			if (current->quoted != 1)
			{
				expanded_value = expand_variable(current->value, shell);
				free(current->value);
				current->value = expanded_value;
			}
		}
		current = current->next;
	}
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

char	*handle_exit_status(char *result, t_shell *shell)
{
	char	*var_value;
	char	*new_result;

	var_value = ft_itoa(shell->exit_status);
	new_result = ft_strjoin_free(result, var_value);
	free(var_value);
	return (new_result);
}

char	*handle_env_variable(char *str, int *i, t_env *env, char *result)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;

	var_name = get_var_name(&str[*i + 1]);
	var_value = get_env_value(var_name, env);
	if (var_value)
		new_result = ft_strjoin_free(result, var_value);
	else
		new_result = ft_strjoin_free(result, "");
	*i += ft_strlen(var_name) + 1;
	free(var_name);
	return (new_result);
}

char	*expand_variable(char *str, t_shell *shell)
{
	int		i;
	char	*result;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				result = handle_exit_status(result, shell);
				i += 2;
			}
			else if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
				result = handle_env_variable(str, &i, shell->env_list, result);
			else
				result = ft_strjoin_char(result, str[i++]);
		}
		else
			result = ft_strjoin_char(result, str[i++]);
	}
	return (result);
}
