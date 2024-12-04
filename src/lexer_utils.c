/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:54:36 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 13:51:47 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_whitespace(char c)
{
	return (c == '\t' || c == '\n' || c == ' ' || c == '\r' || c == '\v');
}

void	set_token(t_token *token, int type, const char *value, int *index)
{
	token->type = type;
	token->value = strdup(value);
	if (!token->value)
	{
		free(token);
		exit_with_error("Memory allocation failed in set_token");
	}
	if (type == TOKEN_REDIRECT_APPEND || type == TOKEN_HEREDOC)
		(*index) += 2;
	else
		(*index)++;
}

int	handle_quote(char *input, int *index,  char **value, int *quote_flag)
{
	char	quote;
	int		start;

	quote = input[*index];
	(*index)++;
	start = *index;
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (input[*index] == quote)
	{
		*value = ft_strndup(&input[start], *index - start);
		if (!*value)
			exit_with_error("Memory allocation failed");
		(*index)++;
		if (quote == '\'')
			*quote_flag = 1;
		else
			*quote_flag = 2;
		return (0);
	}
	else
	{
		display_error("Syntax Error: Unmatched quote");
		return (-1);
	}
}
