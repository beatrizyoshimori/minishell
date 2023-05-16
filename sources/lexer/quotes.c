/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:04:09 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/16 18:23:38 by lucade-s         ###   ########.fr       */
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

static void	mark_metachar_dollar_and_tilde(char *c)
{
	if (*c == '$' && *(c + 1) != '$' && *(c + 1) && !ft_iswhitespace(*(c + 1)))
		*c = DOLLAR_VAR;
	else if (*c == '~' && ft_iswhitespace(*(c - 1)) && *(c + 1) != '~'
		&& (!*(c + 1) || ft_iswhitespace(*(c + 1)) || *(c + 1) == '/'))
		*c = TILDE_VAR;
}

static void	mark_metachar_dollar(char *c)
{
	if (*c == '$' && *(c + 1) != '$' && *(c + 1) && !ft_iswhitespace(*(c + 1)))
		*c = DOLLAR_VAR;
}

void	find_metachar_dollar_and_tilde(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'')
		{
			i++;
			while (prompt[i] && prompt[i] != '\'')
				i++;
		}
		else if (prompt[i] == '\"')
		{
			i++;
			while (prompt[i] && prompt[i] != '\"')
			{
				mark_metachar_dollar(&prompt[i]);
				i++;
			}
		}
		else
			mark_metachar_dollar_and_tilde(&prompt[i]);
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
