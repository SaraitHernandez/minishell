/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:32:49 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/01 15:16:15 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ppx_infile_protector(int *file1)
{
	if (*file1 != -1)
		dup2(*file1, STDIN_FILENO);
	else
		dup2(open("/dev/null", O_RDONLY), STDIN_FILENO);
}

int	ppx_fopen(char *file, char m)
{
	int	fd;

	fd = 0;
	if (m == 'a' || m == 't')
		if (access(file, F_OK) == 0)
			if (access(file, W_OK) != 0)
				ppx_error(1);
	if (m == 'a')
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (m == 't')
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (m == 'r')
	{
		if (access(file, F_OK | R_OK) == 0)
			fd = open(file, O_RDONLY, 0777);
		else
			return (-1);
	}
	if (fd == -1)
		ppx_error(0);
	return (fd);
}

void	ppx_here_doc(t_ast *ast)
{
	int		fd[2];
	pid_t	input;
	int		i;
	char	*line;

	if (pipe(fd) == -1)
		ppx_error(EXIT_FAILURE);
	input = fork();
	if (input == 0)
	{
		close(fd[0]);
		i = 0;
		while ((line = strdup(ast->heredoc_content[i])))
		{
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}
