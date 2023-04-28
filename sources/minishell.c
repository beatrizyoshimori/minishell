/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/28 19:31:10 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	while (!tokens[count])
		count++;
	return (count);
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
	char	**tokens;

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
		tokens = ft_split(prompt, PIPE_SPACE);
		(*ms)->num_tokens = count_tokens(tokens);
		read_tokens(tokens, token, *ms);
		free(prompt);
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
