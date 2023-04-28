/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/28 19:18:13 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char **line)
{
	int	i;
	int	tokens;

	tokens = 1;
	i = 0;
	while (!line[i])
	{
		if (line[i][0] == '|')
			tokens++;
		i++;
	}
	return (tokens);
}

void	read_tokens(char **line, t_token **token, t_ms *ms)
{
	t_token	*new;
	int		i;

	i = 0;
	while (i < ms->num_tokens)
	{
		new = (t_token *)malloc(sizeof(t_token));
		new->token = line[i];
		i++;
	}
}

void	create_prompt(t_token **token, t_ms **ms)
{
	char	*prompt;
	char	**line;

	while (1)
	{
		prompt = readline("bilu> ");
		add_history(prompt);
		metachar_inside_quotes(prompt);
		dollar_inside_quotes(prompt);
		create_spaces(prompt);
		pipe_spaces(prompt);
		redirections_spaces(prompt);
		printf("%s\n", prompt);
		// free(prompt);
		// line = ft_split(prompt, -1);
		// (*ms)->num_tokens = count_commands(line);
		// read_com"mands(line, token, *ms);
	}
}

int	main(void)
{
	t_token	*token;
	t_ms	*ms;

	token = NULL;
	ms = (t_ms *)malloc(sizeof(t_ms));
	create_prompt(&token, &ms);
	return (0);
}
