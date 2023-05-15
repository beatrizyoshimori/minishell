/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:06:19 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/15 15:58:15 by lucade-s         ###   ########.fr       */
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
# define DOLLAR_VAR -5
# define SPACE_OUT_QUOTES -6
# define REMOVE_QUOTES -7
# define LL_MAX 9223372036854775807

typedef struct s_ms
{
	int		num_tokens;
	char	**paths;
	char	**env;
	int		env_nbr_ptr;
	int		exit_status;
}	t_ms;

typedef struct s_token
{
	char			**token;
	char			*pathname;
	char			type;
	int				fd[2];
	pid_t			pid;
	struct s_token	*next;
}	t_token;

extern t_ms	g_ms;

// lexer functions
void	check_ctrl_d(char *prompt);
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
void	set_tokens(char **tokens, t_token **token_list);

// envp utils
void	get_paths(char **envp);
void	copy_envp(char **envp);

// free functions
void	free_ptrptr(char **tokens);
void	free_token_list(t_token **token_list);

// parser functions
void	parser(t_token *token_list);
void	print_syntax_error(t_token *token_list, char c);
void	remove_quotes(t_token *token_list);
void	expand_variable(t_token *token_list);
int		get_length_after_dollar(char *token_i, int *j);
void	found_variable(char **token_i, char *env_i, int **j, int *length);
void	not_found_variable(char **token_i, int **j, int *length);

// exit functions
void	exit_program(t_token **token_list);

// built-in functions

// echo functions
void	echo(t_token *token_list);

// exit_command functions
void	exit_command(t_token *token_list);

// pwd functions
void	pwd(t_token *token_list);

// env functions
void	env(t_token *token_list);

// export functions
void	export(t_token *token_list);
int		check_if_exists(t_token *token_list, int i);
int		check_isname(char *env_i);
void	check_only_export(t_token *token_list);

// non ms functions
void	print_list(t_token **token_list);

#endif