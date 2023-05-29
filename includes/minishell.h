/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:06:19 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/29 20:15:30 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

# define PIPE_SPACE -1
# define PIPE_QUOTES -2
# define L_RDCT_QUOTES -3
# define R_RDCT_QUOTES -4
# define DOLLAR_VAR -5
# define TILDE_VAR -6
# define SPACE_OUT_QUOTES -7
# define REMOVE_QUOTES -8
# define LL_MAX 9223372036854775807
# define NO_REDIRECT 1
# define REDIRECT_INPUT 2
# define REDIRECT_OUTPUT 3
# define REDIRECT_BOTH 6
# define CD 1
# define ECHO 2
# define ENV 3
# define EXIT 4
# define EXPORT 5
# define PWD 6
# define UNSET 7
# define RED_OUT_TRUNC 1
# define RED_OUT_APPEND 2
# define RED_IN 3

typedef struct s_ms
{
	int			num_tokens;
	int			env_nbr_ptr;
	int			*pipe_fd;
	int			printed_error;
	int			backup_fd[2];
	char		**paths;
	char		**env;
	char		*home;
	long long	exit_status;
}	t_ms;

typedef struct s_token
{
	int				redirect;
	int				fd[2];
	int				no_exec;
	int				type;
	char			**token;
	char			*pathname;
	pid_t			pid;
	struct s_token	*next;
}	t_token;

extern t_ms	g_ms;

// built-in folder
// export folder
// export_utils.c functions
int		check_if_exists_exp(char **token, int i);
int		check_isname_exp(char *token_i);
void	check_only_export(char **token);

// export.c functions
void	export(char **token);

// cd folder
// cd_utils.c functions
void	update_pwd_or_oldpwd(char *pwd, char *variable, int length);
char	*get_path(char *variable, int length);

// cd.c functions
void	cd(char **token);

// echo.c functions
void	echo(char **token);

// env.c functions
void	env(char **token);

// exit_command.c functions
void	exit_command(t_token *token_list);

// pwd.c functions
void	pwd(void);

// unset.c functions
void	unset(char **token);

// execution folder
// execution.c functions
void	start_processes(t_token *token_list);

// envp_utils folder
// envp utils
int		dup_env(void);
void	get_paths(char **envp);
void	copy_envp(char **envp);

// exit_free folder
// exit_program_error.c functions
void	exit_program(t_token **token_list);
void	print_error(char *str1, char *str2, char *str3);

// free_utils.c functions
void	free_ptrptr(char **tokens);
void	free_token_list(t_token **token_list);

// built-in_utils.c
void	set_fd_builtin(int redirect, int fd[2]);
void	change_fd_back(int redirect);

// lexer folder
// lexer.c functions
void	check_ctrl_d(char *prompt);
void	check_whitespaces_enter(char **prompt);
void	lexer(char **prompt);

// quote.c functions
void	mark_metachar_inside_quotes(char *prompt);
void	find_metachar_dollar_and_tilde(char *prompt);
void	change_metachar_back(char *prompt);

// space.c functions
void	create_spaces(char **prompt);
void	mark_pipe_spaces(char *prompt);
void	mark_token_spaces(char *prompt);

// parser folder
// parser_tilde_exp.c functions
void	try_find_tilde(char **aux_token_i);

// parser_utils.c functions
void	print_syntax_error(t_token *token_list, char c);
void	remove_quotes(t_token *token_list);

// parser_var_exp_utils.c functions
int		get_length_after_dollar(char *token_i, int *j, int *length);
void	found_variable(char **token_i, char *env_i, int *j, int *length);
void	not_found_variable(char **token_i, int *j, int *length);

// parser_var_exp.c functions
void	expand_variable(t_token *token_list);

// parser.c functions
void	parser(t_token *token_list);

// redirect.c functions
void	redirect_in_out(t_token *token_list);

// heredoc.c functions
void	heredoc(t_token *token, int i);

// token folder
// token_utils.c functions
void	set_tokens(char **tokens, t_token **token_list);

// non ms functions
void	print_list(t_token **token_list);

#endif