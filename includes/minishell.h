/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:06:19 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/26 19:46:46 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
// # include <readline/history.h>

typedef struct s_ms
{
	int	num_cmds;
}	t_ms;

typedef struct s_cmd
{
	char			*cmd;
	char			type;
	struct s_cmd	*next;
}	t_cmd;

int		count_metacharacters(char *prompt);
void	copy_prompt(char *prompt, char *new_prompt);
void	create_spaces(char *prompt);
void	redirections_spaces(char *prompt);
void	pipe_spaces(char *prompt);

#endif