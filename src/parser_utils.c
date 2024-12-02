/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:15:42 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/01 21:23:56 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_word_token(t_token **tokens, char **argv_local, int *argc)
{
	argv_local[(*argc)++] = (*tokens)->value;
	*tokens = (*tokens)->next;
}

int	parse_redirection_token(t_token **tokens, t_red **redirs)
{
	t_token_type	type;
	char			*filename;

	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		display_error("Missing file or delimiter for redirection");
		return (0);
	}
	filename = (*tokens)->value;
	*tokens = (*tokens)->next;
	add_redirection(redirs, create_redirection_node(type, filename));
	return (1);
}

t_ast	*last_left_child(t_ast *ast)
{
	if (!ast)
		return (NULL);
	while (ast->left)
		ast = ast->left;
	return (ast);
}

void	add_redirection(t_red **head, t_red *new_redir)
{
	t_red	*temp;

	if (!*head)
		*head = new_redir;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}
