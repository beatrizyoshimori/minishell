/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:04:09 by lucade-s          #+#    #+#             */
/*   Updated: 2023/04/28 18:59:22 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	metachar_inside_quotes(char *prompt)
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
			while (prompt[i] != c)
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
		i++;
	}
}

void	dollar_inside_quotes(char *prompt)
{
	int		i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'')
		{
			i++;
			while (prompt[i] != '\'')
			{
				if (prompt[i] == '$')
					prompt[i] = DOLLAR_QUOTES;
				i++;
			}
		}
		i++;
	}
}
