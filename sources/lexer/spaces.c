/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:43:25 by lucade-s          #+#    #+#             */
/*   Updated: 2023/04/29 18:48:36 by byoshimo         ###   ########.fr       */
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

void	create_spaces(char **prompt)
{
	size_t	length;
	char	*new_prompt;

	length = ft_strlen(*prompt);
	length += count_metacharacters(*prompt);
	if (length != ft_strlen(*prompt))
	{
		new_prompt = (char *)ft_calloc(length + 1, sizeof(char));
		copy_prompt(*prompt, new_prompt);
		free(*prompt);
		*prompt = ft_strdup(new_prompt);
		free(new_prompt);
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
			while (ft_iswhitespace(prompt[j]) && prompt[j])
				prompt[j--] = PIPE_SPACE;
			j = i + 1;
			while (ft_iswhitespace(prompt[j]) && prompt[j])
				prompt[j++] = PIPE_SPACE;
		}
		i++;
	}
}

void	token_spaces(char *prompt)
{
	int		i;
	char	c;

	i = 0;
	while (prompt[i])
	{
		while (prompt[i] != '\'' && prompt[i] != '\"' && prompt[i])
		{
			if (prompt[i] == ' ')
				prompt[i] = SPACE_OUT_QUOTES;
			i++;
		}
		c = prompt[i];
		if (c != '\0')
		{
			i++;
			while (prompt[i] != c && prompt[i])
				i++;
			i++;
		}
	}
}
