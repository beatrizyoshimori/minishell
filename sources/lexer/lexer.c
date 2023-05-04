/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:27:18 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/03 21:20:34 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_ctrl_d(char *prompt, t_ms **ms)
{
	if (prompt == NULL)
	{
		free(*ms);
		exit (0);
	}
}

static int	check_only_whitespaces(char **prompt)
{
	int	i;

	i = 0;
	while ((*prompt)[i])
	{
		while (ft_iswhitespace((*prompt)[i]))
			i++;
		if (!(*prompt)[i])
			return (0);
		else
			break ;
	}
	return (1);
}

void	check_whitespaces_enter(char **prompt)
{
	while (!(**prompt) || !check_only_whitespaces(prompt))
	{
		add_history(*prompt);
		free(*prompt);
		*prompt = readline("bilu> ");
	}
}

void	lexer(char **prompt)
{
	mark_metachar_inside_quotes(*prompt);
	mark_dollar_inside_quotes(*prompt);
	create_spaces(prompt);
	mark_pipe_spaces(*prompt);
	mark_token_spaces(*prompt);
	change_metachar_back(*prompt);
}
