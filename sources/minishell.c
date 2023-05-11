/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/10 22:22:55 by lucade-s         ###   ########.fr       */
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

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	create_prompt(t_token **token_list, t_ms *ms)
{
	char	*prompt;
	char	**tokens;

	prompt = NULL;
	tokens = NULL;
	while (1)
	{
		prompt = readline("bilu> ");
		check_ctrl_d(prompt, ms);
		check_whitespaces_enter(&prompt);
		add_history(prompt);
		lexer(&prompt);
		tokens = ft_split(prompt, PIPE_SPACE);
		set_tokens(tokens, token_list, ms);
		free(prompt);
		free_ptrptr(tokens);
		parser(token_list, ms);
		echo(*token_list);
		exit_command(*token_list, ms);
		pwd(*token_list);
		env(*token_list);
		export(*token_list);
		free_token_list(token_list);
	}
}

		//print_list(token_list);

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;
	t_ms	*ms;

	(void)argc;
	(void)argv;
	ms = (t_ms *)malloc(sizeof(t_ms));
	copy_envp(envp, ms);
	get_paths(envp, ms);
	token_list = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	create_prompt(&token_list, ms);
	return (0);
}
