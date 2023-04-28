/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:43:25 by lucade-s          #+#    #+#             */
/*   Updated: 2023/04/28 18:58:26 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_metacharacters(char *prompt)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|')
			count += 2;
		else if (prompt[i] == '<')
		{
			if (prompt[i + 1] == '<')
				i++;
			count += 2;
		}
		else if (prompt[i] == '>')
		{
			if (prompt[i + 1] == '>')
				i++;
			count += 2;
		}
		i++;
	}
	return (count);
}

static void	copy_prompt(char *prompt, char *new_prompt)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (prompt[++i])
	{
		++j;
		if (prompt[i] == '|' || prompt[i] == '<' || prompt[i] == '>')
		{
			new_prompt[j] = ' ';
			new_prompt[j + 1] = prompt[i];
			if ((prompt[i] == '<' && prompt[i + 1] == '<')
				|| (prompt[i] == '>' && prompt[i + 1] == '>'))
			{
				new_prompt[j + 2] = prompt[i + 1];
				i++;
				j++;
			}
			new_prompt[j + 2] = ' ';
			j += 2;
		}
		else
			new_prompt[j] = prompt[i];
	}
}

void	create_spaces(char *prompt)
{
	int		length;
	char	*new_prompt;

	length = ft_strlen(prompt);
	length += count_metacharacters(prompt);
	if (length != ft_strlen(prompt))
	{
		new_prompt = (char *)ft_calloc(length + 1, sizeof(char));
		copy_prompt(prompt, new_prompt);
		free(prompt);
		prompt = ft_strdup(new_prompt);
		free(new_prompt);
	}
}

void	redirections_spaces(char *prompt)
{
	int	i;
	int	j;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '>' || prompt[i] == '<')
		{
			j = i - 1;
			while ((prompt[j] >= 9 && prompt[j] <= 13) || prompt[j] == 32)
				prompt[j--] = RDCT_SPACE;
			i++;
			if ((prompt[i - 1] == '>' && prompt[i] == '>')
				|| (prompt[i - 1] == '<' && prompt[i] == '<'))
				i++;
			while ((prompt[i] >= 9 && prompt[i] <= 13) || prompt[i] == 32)
				i++;
			while (!((prompt[i] >= 9 && prompt[i] <= 13) || prompt[i] == 32))
				i++;
			while ((prompt[i] >= 9 && prompt[i] <= 13) || prompt[i] == 32)
				prompt[i++] = RDCT_SPACE;
		}
		i++;
	}
}

void	pipe_spaces(char *prompt)
{
	int	i;
	int	j;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|')
		{
			j = i - 1;
			while ((prompt[j] >= 9 && prompt[j] <= 13) || prompt[j] == 32)
				prompt[j--] = PIPE_SPACE;
			j = i + 1;
			while ((prompt[j] >= 9 && prompt[j] <= 13) || prompt[j] == 32)
				prompt[j++] = PIPE_SPACE;
		}
		i++;
	}
}
