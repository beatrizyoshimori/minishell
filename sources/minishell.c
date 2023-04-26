/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/26 18:48:10 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(char **line)
{
	int	i;
	int	cmds;

	cmds = 1;
	i = 0;
	while (!line[i])
	{
		if (line[i][0] == '|')
			cmds++;
		i++;
	}
	return (cmds);
}

void	read_commands(char **line, t_cmd **cmd, t_ms *ms)
{
	t_cmd	*new;
	int		i;

	i = 0;
	while (i < ms->num_cmds)
	{
		new = (t_cmd *)malloc(sizeof(t_cmd));
		new->cmd = line[i];
		i++;
	}
}

int	count_metacharacters(char *prompt)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|')
			count += 2;
		else if(prompt[i] == '<')
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

void	copy_prompt(char *prompt, char *new_prompt)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (prompt[i])
	{
		if (prompt[i] == '|' || prompt[i] == '<' || prompt[i] == '>')
		{
			new_prompt[j] = ' ';
			new_prompt[j + 1] = prompt[i];
			if ((prompt[i] == '<' && prompt[i + 1] == '<')
				|| (prompt[i] == '>' && prompt[i + 1] == '>'))
			{
				new_prompt[j + 2] = prompt[i + i];
				i++;
				j++;
			}
			new_prompt[j + 2] = ' ';
			j += 2;
		}
		else
			new_prompt[j] = prompt[i];
		i++;
		j++;
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
				prompt[j--] = -2;
			i++;
			if ((prompt[i - 1] == '>' && prompt[i] == '>')
				|| (prompt[i - 1] == '<' && prompt[i] == '<'))
				i++;
			while ((prompt[i] >= 9 && prompt[i] <= 13) || prompt[i] == 32)
				i++;
			while (!((prompt[i] >= 9 && prompt[i] <= 13) || prompt[i] == 32))
				i++;
			while ((prompt[i] >= 9 && prompt[i] <= 13) || prompt[i] == 32)
				prompt[i++] = -2;
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
				prompt[j--] = -1;
			j = i + 1;
			while ((prompt[j] >= 9 && prompt[j] <= 13) || prompt[j] == 32)
				prompt[j++] = -1;
		}
		i++;
	}
}

void	create_prompt(t_cmd **cmd, t_ms **ms)
{
	char	*prompt;
	char	**line;

	while (1)
	{
		prompt = readline("lúbia> ");
		pipe_spaces(prompt);
		redirections_spaces(prompt);
		printf("%s\n", prompt);
		// line = ft_split(prompt, -1);
		// (*ms)->num_cmds = count_commands(line);
		// read_com"mands(line, cmd, *ms);
	}
}

int main(void)
{
	t_cmd	*cmd;
	t_ms	*ms;

	cmd = NULL;
	ms = (t_ms *)malloc(sizeof(t_ms));
	create_prompt(&cmd, &ms);
	return (0);
}