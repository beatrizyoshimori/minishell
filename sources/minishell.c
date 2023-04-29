/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/29 15:00:50 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_token **token_list)
{
	while (*token_list)
	{
		printf("%s\n", (*token_list)->token);
		*token_list = (*token_list)->next;
	}
}

void	create_prompt(t_token **token_list, t_ms **ms)
{
	char	*prompt;
	char	**tokens;

	while (1)
	{
		prompt = readline("bilu> ");
		add_history(prompt);
		metachar_inside_quotes(prompt);
		dollar_inside_quotes(prompt);
		create_spaces(&prompt);
		pipe_spaces(prompt);
		//printf("%p\n", &prompt);
		redirections_spaces(prompt);
		tokens = ft_split(prompt, PIPE_SPACE);
		set_tokens(tokens, token_list, ms);
		print_list(token_list);
		free(prompt);
	}
}

int	main(void)
{
	t_token	*token_list;
	t_ms	*ms;

	token_list = NULL;
	ms = (t_ms *)malloc(sizeof(t_ms));
	create_prompt(&token_list, &ms);
	return (0);
}
