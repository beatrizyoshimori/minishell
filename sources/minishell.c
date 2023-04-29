/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/29 18:40:21 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_token **token_list)
{
	t_token	*aux;

	aux = *token_list;
	while (aux)
	{
		printf("%s\n", aux->token);
		aux = aux->next;
	}
}

void	exit_program(char *prompt, t_ms **ms)
{
	if (!ft_strncmp(prompt, "exit", 5))
	{
		rl_clear_history();
		free(*ms);
		free(prompt);
		exit(0);
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
		exit_program(prompt, ms);
		metachar_inside_quotes(prompt);
		dollar_inside_quotes(prompt);
		create_spaces(&prompt);
		pipe_spaces(prompt);
		token_spaces(prompt);
		change_metachar_back(prompt);
		tokens = ft_split(prompt, PIPE_SPACE);
		set_tokens(tokens, token_list, ms);
		print_list(token_list);
		free_token_list(token_list);
		free(prompt);
		free_split(tokens);
	}
}

		//printf("%p\n", &prompt);

int	main(void)
{
	t_token	*token_list;
	t_ms	*ms;

	token_list = NULL;
	ms = (t_ms *)malloc(sizeof(t_ms));
	create_prompt(&token_list, &ms);
	return (0);
}
