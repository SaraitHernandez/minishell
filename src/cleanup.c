/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:37:57 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/04 15:21:18 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_redirections(t_red *redir)
{
	t_red	*temp;

	while (redir)
	{
		temp = redir;
		redir = redir->next;
		free(temp->filename);
		free(temp);
	}
}

void	free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			free(node->argv[i]);
			i++;
		}
		free(node->argv);
	}
	if (node->redirections)
		free_redirections(node->redirections);
	free(node);
}

static void	free_argument(t_free_type type, void *ptr)
{
	if (ptr == NULL)
		return ;
	if (type == FREE_STRING)
		free(ptr);
	else if (type == FREE_TOKEN)
		free_tokens((t_token *)ptr);
	else if (type == FREE_AST)
		free_ast((t_ast *)ptr);
	else if (type == ERROR_MSG)
		exit_with_error((char *)ptr);
}

void	free_all(int count, ...)
{
	va_list		args;
	t_free_type	type;
	void		*ptr;
	int			i;

	va_start(args, count);
	i = 0;
	while (i < count)
	{
		type = va_arg(args, t_free_type);
		ptr = va_arg(args, void *);
		free_argument(type, ptr);
		i += 1;
	}
	va_end(args);
}
