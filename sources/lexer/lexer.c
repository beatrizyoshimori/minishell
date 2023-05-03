/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:27:18 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/03 19:05:51 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_only_whitespaces(char **prompt)
{
	int	i;

	i = 0;
	while ((*prompt)[i])
	{
		while (ft_iswhitespace((*prompt)[i]))
			i++;
		if (!(*prompt)[i])
		{
			free(*prompt);
			*prompt = readline("bilu> ");
			add_history(*prompt);
			i = 0;
		}
		else
			break ;
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
