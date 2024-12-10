/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 03:03:00 by akacprzy          #+#    #+#             */
/*   Updated: 2024/12/10 13:27:18 by sarherna         ###   ########.fr       */
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

static char	*ppx_command_abs_path(t_ast *ast)
{
	if (access(ast->argv[0], X_OK) == 0)
		return (ast->argv[0]);
	return (NULL);
}

static char	*ppx_cmd_path(t_ast *ast, t_env *env, t_ast *past)
{
	char	**list_path;
	char	*part_path;
	char	*full_path;
	int		i;

	if (!get_env_value("PATH", env))
		ppx_error_path(127, ast, env, past);
	list_path = ft_split(get_env_value("PATH", env), ':');
	i = 0;
	while (list_path[i] && ast->argv[0][0] != '\0')
	{
		part_path = ft_strjoin(list_path[i], "/");
		full_path = ft_strjoin(part_path, ast->argv[0]);
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

static void	ppx_cmd_exec(t_ast *ast, t_shell *shell, t_ast *past,
				struct sigaction *sa_old)
{
	char	*path;
	int		len;
	char	**env_arr;

	sigaction(SIGINT, sa_old, NULL);
	signal(SIGINT, SIG_DFL);
	path = ppx_command_abs_path(ast);
	if (!path)
		path = ppx_cmd_path(ast, shell->env_list, past);
	if (!path)
		ppx_error_cmd_not_found(127, ast, shell->env_list, past);
	env_arr = list_to_array(shell->env_list, 0);
	len = env_array_len(env_arr);
	if (execve(path, ast->argv, env_arr))
	{
		free_array(len, env_arr);
		shell->exit_status = errno;
		ppx_error(errno, ast, shell->env_list, past);
	}
	free_array(len, env_arr);
	free_env_list(shell->env_list);
	free_ast(ast);
	shell->exit_status = SUCCESS;
	exit(shell->exit_status);
}

void	ppx_child(t_ast *ast, t_shell *shell, t_ast *past)
{
	pid_t				pid;
	int					status;
	struct sigaction	sa_old;

	setup_child_signal_handlers(&sa_old);
	pid = fork();
	if (pid == -1)
		ppx_error(EXIT_FAILURE, ast, shell->env_list, past);
	if (pid == 0)
		ppx_cmd_exec(ast, shell, past, &sa_old);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
		else if (WIFSTOPPED(status))
			shell->exit_status = 128 + WSTOPSIG(status);
		else
			shell->exit_status = status;
		setup_signal_handlers();
	}
}
