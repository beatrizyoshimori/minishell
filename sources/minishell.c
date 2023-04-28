/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/28 18:45:54 by byoshimo         ###   ########.fr       */
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

void	create_prompt(t_cmd **cmd, t_ms **ms)
{
	char	*prompt;
	char	**line;

	while (1)
	{
		prompt = readline("bilu> ");
		metachar_inside_quotes(prompt);
		dollar_inside_quotes(prompt);
		create_spaces(prompt);
		pipe_spaces(prompt);
		redirections_spaces(prompt);
		printf("%s\n", prompt);
		// free(prompt);
		// line = ft_split(prompt, -1);
		// (*ms)->num_cmds = count_commands(line);
		// read_com"mands(line, cmd, *ms);
	}
}

int	main(void)
{
	t_cmd	*cmd;
	t_ms	*ms;

	cmd = NULL;
	ms = (t_ms *)malloc(sizeof(t_ms));
	create_prompt(&cmd, &ms);
	return (0);
}
