/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/01 17:04:24 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_token **token_list)
{
	int		i;
	t_token	*aux;

	aux = *token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			printf("%s\n", aux->token[i]);
			i++;
		}
		printf("\n");
		aux = aux->next;
	}
}

void	create_prompt(t_token **token_list, t_ms **ms)
{
	char	*prompt;
	char	**tokens;

	prompt = NULL;
	tokens = NULL;
	while (1)
	{
		prompt = readline("bilu> ");
		add_history(prompt);
		exit_command(prompt, ms);
		metachar_inside_quotes(prompt);
		dollar_inside_quotes(prompt);
		create_spaces(&prompt);
		pipe_spaces(prompt);
		token_spaces(prompt);
		change_metachar_back(prompt);
		tokens = ft_split(prompt, PIPE_SPACE);
		set_tokens(tokens, token_list, ms);
		free(prompt);
		free_split(tokens);
		print_list(token_list);
		parser(token_list, ms);
		free_token_list(token_list);
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
