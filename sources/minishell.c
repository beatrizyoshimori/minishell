/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/24 21:53:02 by byoshimo         ###   ########.fr       */
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

t_cmd	*ft_cmd_last(t_cmd *cmd)
{
	if (cmd == NULL)
		return (cmd);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	ft_cmd_last(*cmd)->next = new;
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
		
	}
}

void	create_prompt(t_cmd **cmd, t_ms **ms)
{
	char	*prompt;
	char	**line;

	while (1)
	{
		prompt = readline("lúbia> ");
		printf("%s\n", prompt);
		line = ft_split(prompt, ' ');
		(*ms)->num_cmds = count_commands(line);
		read_commands(line, cmd, *ms);
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