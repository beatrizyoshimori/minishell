/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:04:09 by lucade-s          #+#    #+#             */
/*   Updated: 2023/04/26 20:10:28 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void	metachar_inside_quotes(char *prompt)
{
	int	i;

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
					prompt[i] = -3;
				else if (prompt[i] == '<')
					prompt[i] = -4;
				else if (prompt[i] == '>')
					prompt[i] = -5;
				i++;
			}
		}
		i++;
	}
}
