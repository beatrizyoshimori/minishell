/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:06:19 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/29 18:49:43 by byoshimo         ###   ########.fr       */
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
	char			*token;
	char			**cmd;
	char			type;
	struct s_token	*next;
}	t_token;

// space functions
void	create_spaces(char **prompt);
void	pipe_spaces(char *prompt);
void	token_spaces(char *prompt);

// quote functions
void	metachar_inside_quotes(char *prompt);
void	dollar_inside_quotes(char *prompt);
void	change_metachar_back(char *prompt);

// token list utils
void	set_tokens(char **tokens, t_token **token_list, t_ms **ms);

// free functions
void	free_split(char **tokens);
void	free_token_list(t_token **token_list);

#endif