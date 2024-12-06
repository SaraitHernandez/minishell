/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akacprzy <akacprzy@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:03:00 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/06 01:47:25 by akacprzy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ppx_free_lst(char **list)
{
	int		i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
}

static char	*ppx_cmd_path(char *cmd, t_env *env)
{
	char	**list_path;
	char	*part_path;
	char	*full_path;
	int		i;

	if (!get_env_value("PATH", env))
		ppx_error_path(127, cmd);
	list_path = ft_split(get_env_value("PATH", env), ':');
	i = 0;
	while (list_path[i])
	{
		part_path = ft_strjoin(list_path[i], "/");
		full_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(full_path, X_OK) == 0)
		{
			ppx_free_lst(list_path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ppx_free_lst(list_path);
	return (0);
}

void	ppx_cmd_exec(char **argv, t_shell *shell)
{
	char	*path;
	int		len;
	char	**env_arr;

	path = ppx_cmd_path(argv[0], shell->env_list);
	if (!path)
		ppx_error_cmd_not_found(127, argv[0]);
	env_arr = list_to_array(shell->env_list, 0);
	len = env_array_len(env_arr);
	if (execve(path, argv, env_arr))
	{
		free(path);
		free_array(len, env_arr);
		ppx_error(errno);
	}
	free_array(len, env_arr);
	exit(SUCCESS);
}

void	ppx_child(t_ast *ast, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ppx_error(EXIT_FAILURE);
	if (pid == 0)
	{
		ppx_cmd_exec(ast->argv, shell);
		exit(shell->exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
}
