/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:48:45 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 15:02:29 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_word_quotes(char *input, int *index,
						char **value, int *quote)
{
	char	*part;
	int		ret;

	ret = handle_quote(input, index, &part, quote);
	if (ret == -1)
		return (-1);
	*value = ft_strjoin_free(*value, part);
	free(part);
	return (0);
}

static int	handle_word_regular(char *input, int *index, char **value)
{
	int		start;
	char	*part;

	start = *index;
	while (input[*index] && !is_whitespace(input[*index])
		&& !is_operator(input[*index]) && !is_quote(input[*index]))
		(*index)++;
	part = ft_strndup(&input[start], *index - start);
	*value = ft_strjoin_free(*value, part);
	free(part);
	return (0);
}

int	handle_word(t_token *token, char *input, int *index)
{
	int		quote;
	char	*value;

	quote = 0;
	value = ft_strdup("");
	while (input[*index] && !is_whitespace(input[*index])
		&& !is_operator(input[*index]))
	{
		if (is_quote(input[*index]))
		{
			if (handle_word_quotes(input, index, &value, &quote) == -1)
			{
				free(value);
				return (-1);
			}
		}
		else
			handle_word_regular(input, index, &value);
	}
	token->type = TOKEN_WORD;
	token->quoted = quote;
	token->value = value;
	return (0);
}
