/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarherna <sarait.hernandez@novateva.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:04:15 by sarherna          #+#    #+#             */
/*   Updated: 2024/12/10 13:24:32 by sarherna         ###   ########.fr       */
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
# include <limits.h>
# include <stdarg.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "libft.h"

/* Constants */
# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 4096
# define STDIN_FD 0
# define STDOUT_FD 1
# define STDERR_FD 2
# define ERROR 1
# define SUCCESS 0
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

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
// 0: No quotes, 1: Single quotes, 2: Double quotes
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	int					quoted;
	struct s_token		*next;
}	t_token;

/* Command AST Node Types */
typedef enum e_ast_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECTION,
	NODE_HEREDOC
}	t_ast_type;

/* Struct for redirection */

typedef struct s_redirection
{
	t_token_type			type;
	char					*filename;
	char					quoted;
	int						fd;
	struct s_redirection	*next;
}	t_red;

/* Struct for Abstract Syntax Tree Nodes */
typedef struct s_ast
{
	t_ast_type			type;
	char				**argv;
	t_red				*redirections;
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

/* Struct for free Variables */
typedef enum e_free_type
{
	FREE_STRING,
	FREE_TOKEN,
	FREE_AST,
	ERROR_MSG,
}	t_free_type;

/* Struct for Shell State */
typedef struct s_shell
{
	t_env	*env_list;
	int		exit_status;
	int		do_exit;
	int		in_pipe;
}	t_shell;

/* Global Variable for Signal Handling */
extern volatile sig_atomic_t	g_signal_received;

/* Function Prototypes */

/* main.c */
int			main(int argc, char **argv, char **envp);
void		shell_loop(t_shell *shell);

/* main_utils.c */
int			check_interrupt(char *input);
int			check_ast_null(char *input, t_token *tokens, t_ast *ast);
void		debug_print(t_token *tokens, t_ast *ast);

/* init_shell.c */
void		init_shell_env(char **envp, t_shell *shell);
void		set_shell_level(t_env *env);

/* lexer.c */
t_token		*lexer(char *input);

/* lexer_utils.c */
int			is_operator(char c);
int			is_quote(char c);
int			is_whitespace(char c);
int			handle_quote(char *input, int *index, char **value,
				int *quote_flag);
void		set_token(t_token *token, int type, const char *value, int *index);
t_token		*tokenize(char *input, int *index);
int			handle_word(t_token *token, char *input, int *index);

/* expand_variables.c */
void		expand_tokens(t_token *tokens, t_shell *shell);
char		*expand_variable(char *str, t_shell *shell);

/* heredoc and utils.c */
int			handle_heredoc_interrupt(int fd);
int			process_heredocs(t_ast *cmd, t_shell *shell);
int			handle_single_heredoc(t_red *redir, t_shell *shell, t_ast *ast);

/* parser.c */
t_ast		*parse_tokens(t_token *tokens, t_shell *shell);

/* parser_utils.c & nodes */
void		parse_word_token(t_token **tokens, char **argv_local, int *argc);
int			parse_redirection_token(t_token **tokens, t_red **redirs);
void		add_redirection(t_red **head, t_red *new_redir);
int			is_redirection(t_token_type type);
t_red		*create_redirection_node(t_token_type type, char *filename,
				int quoted);
int			parse_command_elements(t_token **tokens, char **argv_local,
				int *argc, t_red **redirs);
t_ast		*create_command_node(char **argv_local, int argc, t_red *redirs);
t_ast		*create_pipe_node(t_ast *left, t_ast *right);

/* executor.c */
void		execute_ast(t_ast *ast, t_shell *shell, t_ast *past);

/* exec_utils.c */
void		ppx_child(t_ast *ast, t_shell *shell, t_ast *past);

/* exec_pipes.c */
void		ppx_pipe(t_ast *ast, t_shell *shell);

/* exec_errors.c */
void		ppx_error(int errn, t_ast *ast, t_env *env, t_ast *past);
void		ppx_error_path(int errn, t_ast *ast, t_env *env, t_ast *past);
void		ppx_error_cmd_not_found(int errn, t_ast *ast, t_env *env,
				t_ast *past);

/* exec_builtins.c */
int			is_builtin(char *cmd);
void		exec_builtin(char **args, t_shell *shell);

/* redirection.c */
int			handle_redirection(t_red *redirs);

/* signals.c */
void		sigint_handler(int signo);
void		setup_signal_handlers(void);
void		handle_heredoc_child(t_red *redir, t_shell *shell, int write_fd);
void		heredoc_sigint_handler(int signo);
void		setup_child_signal_handlers(struct sigaction *sa_old);

/* cleanup.c */
void		cleanup_shell(t_env *env, t_ast *ast);
void		free_ast(t_ast *ast);
void		free_tokens(t_token *tokens);
void		free_all(int count, ...);
void		free_redirections(t_red *redir);

/* builtins/builtin_echo.c */
int			bin_echo(char **argv);

/* builtins/builtin_cd.c */
int			bin_cd(char **argv, t_env *env);

/* builtins/builtin_pwd.c */
int			bin_pwd(void);

/* builtins/builtin_export.c */
void		bin_export(char **args, t_shell *shell);
void		add_env_variable(char *assignment, t_env *env);

/* builtins/builtin_unset.c */
int			bin_unset(char **argv, t_env *env);
void		remove_env_variable(char *var_name, t_env *env);

/* builtins/builtin_env.c */
int			bin_env(t_env *env);

/* builtins/builtin_exit.c */
void		bin_exit(char **args, t_shell *shell);

/* environment/environment.c */
t_env		*copy_environment(char **envp);
char		*get_env_value(char *key, t_env *env);
void		set_env_value(char *key, char *value, t_env **env);
void		unset_env_value(char *key, t_env *env);

/* environment/environment_variables.c */
void		ensure_path_variable(t_env *env);

/* environment/environment_utils.c */
t_env		*create_env_node(char *key, char *value);
void		free_env_list(t_env *env);
char		**env_list_to_array(t_env *env);
void		add_env_node(t_env **env_list, t_env *new_node);
t_env		*parse_env_var(char *env_var);

/* environment/environment_export.c */
int			env_array_len(char **env);
void		env_export_print(t_env *env);

/* utils/utils_arrays.c */
void		free_array(int i, char **array);
char		**list_to_array(t_env *env_list, int full);

/* utils/utils_strings.c */
char		*concat_content(char *existing, char *new_line);
char		*ft_strndup(const char *s, size_t n);

char		**copy_argv(char **argv_local, int argc);

/* utils/utils_memory.c */
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin_char(char *s1, char c);

/* utils/utils_errors.c */
void		display_error(char *message);
void		exit_with_error(char *message);
void		command_not_found(char *cmd_name);
void		redir_error(char *filename);

/* tests/test_parser.c */
const char	*token_type_to_string(t_token_type type);
const char	*ast_type_to_string(t_ast_type type);
void		print_tokens(t_token *tokens);
const char	*redirect_type_to_string(int redirect_type);
void		print_ast_recursive(t_ast *ast, int depth);
void		print_ast(t_ast *ast);
void		print_indentation(int depth);
#endif