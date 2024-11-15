/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:04:15 by sarherna          #+#    #+#             */
/*   Updated: 2024/11/14 20:11:35 by sarherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard Library Includes */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Constants */
# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 1024
# define STDIN_FD 0
# define STDOUT_FD 1
# define STDERR_FD 2

/* Token Types */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

/* Struct for Tokens */
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

/* Command AST Node Types */
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECTION,
	NODE_SEQUENCE
}	t_node_type;

/* Struct for Abstract Syntax Tree Nodes */
typedef struct s_ast
{
	t_node_type			type;
	char				**argv;
	char				*filename;
	int					append;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

/* Struct for Environment Variables */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* Global Variable for Signal Handling */
extern volatile sig_atomic_t	g_signal_received;

/* Function Prototypes */

/* main.c */
int		main(int argc, char **argv, char **envp);
void	shell_loop(void);

/* init_shell.c */
void	init_shell_env(char **envp);
void	set_shell_level(void);
void	init_signal_handlers(void);

/* input.c */
char	*read_input(void);
void	handle_eof(char *line);
void	add_history_line(char *line);

/* lexer.c */
t_token	*lexer(char *input);
t_token	*tokenize(char *input, int *index);
int		is_operator(char c);
int		is_quote(char c);

/* expand_variables.c */
void	expand_tokens(t_token *tokens, t_env *env);
char	*expand_variable(char *str, int *index, t_env *env);
char	*get_variable_value(char *var_name, t_env *env);

/* parser.c */
t_ast	*parse_tokens(t_token *tokens);
t_ast	*parse_pipeline(t_token **tokens);
t_ast	*parse_command(t_token **tokens);
t_ast	*parse_redirections(t_ast *cmd, t_token **tokens);

/* parser_utils.c */
int		is_redirection(t_token_type type);
void	syntax_error(char *message);
t_ast	*create_command_node(char **argv);

/* executor.c */
void	execute_ast(t_ast *ast);
void	execute_pipeline(t_ast *pipeline);
void	execute_command(t_ast *cmd);
void	setup_redirections(t_ast *cmd);

/* exec_utils.c */
char	*find_executable(char *cmd_name, t_env *env);
int		is_builtin(char *cmd_name);
void	execute_builtin(t_ast *cmd, t_env *env);

/* redirection.c */
int		handle_input_redirection(char *filename);
int		handle_output_redirection(char *filename, int append);
int		handle_heredoc(char *delimiter);
void	restore_standard_fds(int stdin_copy, int stdout_copy);

/* pipes.c */
int		setup_pipes(int pipefd[2]);
void	close_pipes(int pipefd[2]);
void	redirect_pipes(int input_fd, int output_fd);

/* signals.c */
void	sigint_handler(int signo);
void	sigquit_handler(int signo);
void	setup_signal_handlers(void);
void	heredoc_signal_handler(int signo);

/* cleanup.c */
void	cleanup_shell(t_env *env, t_ast *ast);
void	free_ast(t_ast *ast);
void	free_tokens(t_token *tokens);

/* builtins/builtin_echo.c */
int		builtin_echo(char **argv);

/* builtins/builtin_cd.c */
int		builtin_cd(char **argv, t_env *env);

/* builtins/builtin_pwd.c */
int		builtin_pwd(void);

/* builtins/builtin_export.c */
int		builtin_export(char **argv, t_env *env);
void	add_env_variable(char *assignment, t_env *env);

/* builtins/builtin_unset.c */
int		builtin_unset(char **argv, t_env *env);
void	remove_env_variable(char *var_name, t_env *env);

/* builtins/builtin_env.c */
int		builtin_env(t_env *env);

/* builtins/builtin_exit.c */
int		builtin_exit(char **argv);

/* environment/environment.c */
t_env	*copy_environment(char **envp);
char	*get_env_value(char *key, t_env *env);
void	set_env_value(char *key, char *value, t_env *env);
void	unset_env_value(char *key, t_env *env);

/* environment/environment_utils.c */
t_env	*create_env_node(char *key, char *value);
void	free_env_list(t_env *env);
char	**env_list_to_array(t_env *env);

/* utils/utils_strings.c */
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	**ft_split(const char *s, char c);

/* utils/utils_memory.c */
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	free_string_array(char **array);

/* utils/utils_errors.c */
void	display_error(char *message);
void	exit_with_error(char *message, int exit_code);
void	command_not_found(char *cmd_name);

/* Other Utility Functions */
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif