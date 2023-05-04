/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:06:19 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/03 21:20:11 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE_SPACE -1
# define PIPE_QUOTES -2
# define L_RDCT_QUOTES -3
# define R_RDCT_QUOTES -4
# define DOLLAR_QUOTES -5
# define SPACE_OUT_QUOTES -6

typedef struct s_ms
{
	int	num_tokens;
}	t_ms;

typedef struct s_token
{
	char			**token;
	char			type;
	struct s_token	*next;
}	t_token;

// lexer functions
void	check_ctrl_d(char *prompt, t_ms **ms);
void	check_whitespaces_enter(char **prompt);
void	lexer(char **prompt);

// space functions
void	create_spaces(char **prompt);
void	mark_pipe_spaces(char *prompt);
void	mark_token_spaces(char *prompt);

// quote functions
void	mark_metachar_inside_quotes(char *prompt);
void	mark_dollar_inside_quotes(char *prompt);
void	change_metachar_back(char *prompt);

// token list utils
void	set_tokens(char **tokens, t_token **token_list, t_ms **ms);

// free functions
void	free_split(char **tokens);
void	free_token_list(t_token **token_list);

// parser functions
void	parser(t_token **token_list, t_ms **ms);
void	print_syntax_error(t_token **token_list, t_ms **ms, char c);

// exit functions
void	exit_command(char *prompt, t_ms **ms);
void	exit_program(t_token **token_list, t_ms **ms);

#endif