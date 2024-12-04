/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:36:40 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 14:59:33 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*add_token_to_list(t_token **head,
					t_token *new_token, t_token *current)
{
	if (!*head)
	{
		*head = new_token;
		return (new_token);
	}
	else
	{
		current->next = new_token;
		return (new_token);
	}
}

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	int		index;

	head = NULL;
	current = NULL;
	index = 0;
	while (1)
	{
		new_token = tokenize(input, &index);
		if (!new_token)
		{
			free_tokens(head);
			return (NULL);
		}
		current = add_token_to_list(&head, new_token, current);
		if (new_token->type == TOKEN_EOF)
			break ;
	}
	return (head);
}
