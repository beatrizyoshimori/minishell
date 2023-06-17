/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:06:19 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/17 15:01:03 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

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
# include <dirent.h>

# define PIPE_SPACE -1
# define PIPE_QUOTES -2
# define L_RDCT_QUOTES -3
# define R_RDCT_QUOTES -4
# define DOLLAR_VAR -5
# define TILDE_VAR -6
# define SPACE_OUT_QUOTES -7
# define REMOVE_QUOTES -8
# define WILDCARDS -9
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
	char			**paths;
	char			**env;
	char			*home;
	pid_t			*pid;
	long long		exit_status;
	struct s_token	*token_list;
	int				num_tokens;
	int				env_nbr_ptr;
	int				*pipe_fd;
	int				syntax_error;
	int				on_fork;
	int				print_error;
	int				fd_heredoc;
	int				first_heredoc;
	int				first_wildcard;
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

// sources folders
// built-in folder
// cd folder
// cd_utils.c functions
void	update_pwd_or_oldpwd(char *pwd, char *variable, int length);
char	*get_path(char *variable, int length);

// cd.c functions
void	cd(char **token);

// export folder
// export_utils.c functions
int		check_if_exists_exp(char **token, int i);
int		check_isname_exp(char *token_i);
void	check_only_export(char **token);

// export.c functions
void	export(char **token);

// built-in_utils.c functions
void	exec_builtin(t_token *token_list, t_token *token);
int		ft_isbuiltin(t_token *token_list);

// echo.c functions
void	echo(char **token);

// env.c functions
void	env(char **token);

// exit_command.c functions
void	exit_command(t_token *token_list, char **token);

// pwd.c functions
void	pwd(void);

// unset.c functions
void	unset(char **token);

// envp_utils folder
// envp_utils.c functions
int		dup_env(void);
void	get_paths(void);
void	copy_envp(char **envp);

// error_free folder
// error_utils.c functions
void	print_error(char *str1, char *str2, char *str3, int exit_status);
void	print_error_heredoc(char *prompt, char *dlmt);

// free_utils.c functions
void	free_ptrptr(char **ptrptr);
void	free_token_list(t_token **token_list);

// execution folder
// execution_command.c functions
void	exit_process(t_token *token_list);
void	exec_command_child(t_token *token_list, t_token *token);

// execution_fd.c functions
void	close_fd(t_token *token_list);
void	create_pipes(void);
void	set_fd(t_token *token, int i);

// execution_pathname.c functions
void	set_pathname(t_token *token);

// execution_utils.c functions
int		ft_isfile(char *token_cmd);
int		ft_isdirectory(char *token_cmd);

// execution.c functions
void	start_processes(t_token *token_list);

// lexer folder
// lexer.c functions
void	check_ctrl_d(char *prompt);
void	check_whitespaces_enter(char **prompt);
void	lexer(char **prompt);

// spaces.c functions
void	create_spaces(char **prompt);
void	mark_pipe_spaces(char *prompt);
void	mark_token_spaces(char *prompt);

// parser folder
// parser_tilde_exp.c functions
void	try_find_tilde(char **token_i);

// parser_utils.c functions
void	check_pipe_error(t_token *token_list);
void	print_syntax_error(char *c);
void	remove_quotes_aux(char **token_i);
void	mark_quotes(char **token_i, int *j);
void	remove_quotes(t_token *token_list);

// parser_var_exp_utils.c functions
int		get_length_after_dollar(char *token_i, int *j, int *length);
void	found_variable(char **tpidoken_i, char *env_i, int *j, int *length);
void	not_found_variable(char **token_i, int *j, int *length);

// parser_var_exp.c functions
void	put_exit_status(char **token_i, int *j);
void	try_find_variable(char **token_i, int *j);
void	expand_variable(t_token *token_list);

// redirect folder
// heredoc.c functions
void	heredoc(t_token *token, int i);
void	redirect_heredoc(t_token *token_list);

// redirect_utils.c functions
void	update_token(char **token);

// redirect.c functions
void	redirect_input(t_token *token, int i, int *ver);
void	redirect_in_out(t_token *token_list);

// signal folder
// signal_handlers.c functions
void	signal_handler_parent(void);
void	signal_handler_child(void);
void	signal_handler_heredoc(int signal);

// token folder
// token_utils.c functions
void	set_tokens(char **tokens, t_token **token_list);

// sources_bonus folder
// lexer_bonus folder
// quotes.c functions
void	mark_metachar_inside_quotes(char *prompt);
void	find_metachar(char *prompt);
void	change_metachar_back(char *prompt);

// parser_bonus folder
// parser.c functions
void	parser(t_token *token_list);

// wildcards_bonus folder
// wildcards_bonus.c functions
t_list	*get_wildcards_expansion(char *token_i, char *path_prev);
void	wildcards(t_token *token_list);

// wildcards_exp_aux_bonus.c functions
void	aux_get_wildcards(char *token_i, t_list *files);

// wildcards_exp_bonus.c functions
char	*get_path_wc(char *token_i, char *path_prev, char **aux_token);
int		get_files(t_list **files, char *path, char *aux_token);
void	free_all_wc(t_list *files, char *path,
			char *aux_token, char *aux_token2);
void	delete_node_list(t_list **files);

// wildcards_exp_put_bonus.c functions
void	put_wildcards(t_token *token, int *i, char *first_path, t_list *wc);

// wildcards_list_utils_bonus.c functions
int		check_empty_subfiles(t_list *files, char *path,
			char *aux_token, char *aux_token2);
void	free_list(t_list **files);
void	cat_files(t_list **dir, t_list *sub_files);
void	put_slash_dir(t_list **files);
t_list	*copy_list(t_list *files);

// wildcards_utils_bonus.c functions
int		ft_strchr_wc(const char *s);
int		end_with_slash(char *token_i);
int		get_first_path(char *token_i, char **first_path);
char	**copy_ptrptr(char **ptrptr);
void	change_back_asterisc(char **token_i);

void	free_all_wc(t_list *files, char *path,
			char *aux_token, char *aux_token2);

#endif