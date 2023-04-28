/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:06:19 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/28 19:17:44 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PIPE_SPACE -1
# define RDCT_SPACE -2
# define PIPE_QUOTES -3
# define L_RDCT_QUOTES -4
# define R_RDCT_QUOTES -5
# define DOLLAR_QUOTES -6

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
void	create_spaces(char *prompt);
void	redirections_spaces(char *prompt);
void	pipe_spaces(char *prompt);

// quote functions
void	metachar_inside_quotes(char *prompt);
void	dollar_inside_quotes(char *prompt);

#endif