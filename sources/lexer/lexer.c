/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:27:18 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/03 19:01:10 by lucade-s         ###   ########.fr       */
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
	metachar_inside_quotes(*prompt);
	dollar_inside_quotes(*prompt);
	create_spaces(prompt);
	pipe_spaces(*prompt);
	token_spaces(*prompt);
	change_metachar_back(*prompt);
}
