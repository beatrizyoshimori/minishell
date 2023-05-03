/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:04:09 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/03 19:03:51 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mark_metachar_inside_quotes(char *prompt)
{
	int		i;
	char	c;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\"' || prompt[i] == '\'')
		{
			c = prompt[i];
			i++;
			while (prompt[i] && prompt[i] != c)
			{
				if (prompt[i] == '|')
					prompt[i] = PIPE_QUOTES;
				else if (prompt[i] == '<')
					prompt[i] = L_RDCT_QUOTES;
				else if (prompt[i] == '>')
					prompt[i] = R_RDCT_QUOTES;
				i++;
			}
		}
		if (prompt[i] != '\0')
			i++;
	}
}

void	mark_dollar_inside_quotes(char *prompt)
{
	int		i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'')
		{
			i++;
			while (prompt[i] && prompt[i] != '\'')
			{
				if (prompt[i] == '$')
					prompt[i] = DOLLAR_QUOTES;
				i++;
			}
		}
		if (prompt[i] != '\0')
			i++;
	}
}

void	change_metachar_back(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == PIPE_QUOTES)
			prompt[i] = '|';
		else if (prompt[i] == L_RDCT_QUOTES)
			prompt[i] = '<';
		else if (prompt[i] == R_RDCT_QUOTES)
			prompt[i] = '>';
		i++;
	}
}
