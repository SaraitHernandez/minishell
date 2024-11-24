/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:37:57 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/24 18:38:18 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token *tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_ast(t_ast *node)
{
	if (!node)
		return;
	free_ast(node->left);
	free_ast(node->right);
	if (node->argv)
		free(node->argv);
	if (node->filename)
		free(node->filename);
	free(node);
}
