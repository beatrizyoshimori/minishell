/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:06:19 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/12 22:03:44 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE_SPACE -1
# define PIPE_QUOTES -2
# define L_RDCT_QUOTES -3
# define R_RDCT_QUOTES -4
# define DOLLAR_QUOTES -5
# define SPACE_OUT_QUOTES -6
# define LL_MAX 9223372036854775807

typedef struct s_ms
{
	int			num_tokens;
	char		**paths;
	char		**env;
	char		**env_export;
	int			env_nbr_ptr;
	int			env_exp_nbr_ptr;
	long long	status;
}	t_ms;

typedef struct s_token
{
	char			**token;
	char			*pathname;
	char			type;
	int				fd[2];
	pid_t			pid;
	struct s_ms		*ms;
	struct s_token	*next;
}	t_token;

// lexer functions
void	check_ctrl_d(char *prompt, t_ms *ms);
void	check_whitespaces_enter(char **prompt);
void	lexer(char **prompt);

// space functions
void	create_spaces(char **prompt);
void	mark_pipe_spaces(char *prompt);
void	mark_token_spaces(char *prompt);

// quote functions
void	mark_metachar_inside_quotes(char *prompt);
void	find_metachar_dollar(char *prompt);
void	change_metachar_back(char *prompt);

// token list utils
void	set_tokens(char **tokens, t_token **token_list, t_ms *ms);

// envp utils
void	get_paths(char **envp, t_ms *ms);
void	copy_envp(char **envp, t_ms *ms);
char	*copy_env_export(char *envp_i);

// free functions
void	free_ptrptr(char **tokens);
void	free_token_list(t_token **token_list);

// parser functions
void	parser(t_token **token_list, t_ms *ms);
void	print_syntax_error(t_token **token_list, t_ms *ms, char c);

// exit functions
void	exit_program(t_token **token_list, t_ms *ms);

// built-in functions

// echo functions
void	echo(t_token *token_list);

// exit_command functions
void	exit_command(t_token *token_list, t_ms *ms);

// pwd functions
void	pwd(t_token *token_list);

// env functions
void	env(t_token *token_list);

// export functions
void	export(t_token *token_list);
int		check_if_exists(t_token *token_list, int i);
int		check_isname(char *env_i);
void	check_only_export(t_token *token_list);

#endif