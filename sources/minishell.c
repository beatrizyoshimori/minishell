/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/26 18:27:29 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	g_ms;

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	make_command(t_token *token_list)
{
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		if (aux->token[0])
		{
			if (!ft_strncmp(aux->token[0], "cd", 2))
				cd(aux->token);
			else if (!ft_strncmp(aux->token[0], "export", 7))
				export(aux->token);
			else if (!ft_strncmp(aux->token[0], "echo", 5))
				echo(aux->token);
			else if (!ft_strncmp(aux->token[0], "env", 4))
				env(aux->token);
			else if (!ft_strncmp(aux->token[0], "exit", 5))
				exit_command(token_list);
			else if (!ft_strncmp(aux->token[0], "pwd", 4))
				pwd();
			else if (!ft_strncmp(aux->token[0], "unset", 6))
				unset(aux->token);
		}
		aux = aux->next;
	}
}

static void	exec_command(t_token *token_list)
{
	if (g_ms.num_tokens == 1)
	{
		if (!ft_strncmp(token_list->token[0], "cd", 3))
			cd(token_list->token);
		else if (!ft_strncmp(token_list->token[0], "export", 7))
			export(token_list->token);
		else if (!ft_strncmp(token_list->token[0], "echo", 5))
			echo(token_list->token);
		else if (!ft_strncmp(token_list->token[0], "env", 4))
			env(token_list->token);
		else if (!ft_strncmp(token_list->token[0], "exit", 5))
			exit_command(token_list);
		else if (!ft_strncmp(token_list->token[0], "pwd", 4))
			pwd();
		else if (!ft_strncmp(token_list->token[0], "unset", 6))
			unset(token_list->token);
		else
			start_processes(token_list);
	}
	else
		start_processes(token_list);
}

void	create_prompt(t_token **token_list)
{
	char	*prompt;
	char	**tokens;

	while (1)
	{
		prompt = readline("bilu> ");
		check_ctrl_d(prompt);
		check_whitespaces_enter(&prompt);
		add_history(prompt);
		lexer(&prompt);
		tokens = ft_split(prompt, PIPE_SPACE);
		set_tokens(tokens, token_list);
		free(prompt);
		free_ptrptr(tokens);
		parser(*token_list);
		// print_list(token_list);
		if ((*token_list)->token[0] && !ft_strncmp((*token_list)->token[0], "exit", 5) && !(*token_list)->next)
			break ;
		if ((*token_list)->token[0])
			start_processes(*token_list);
		exec_command(*token_list);
		free_token_list(token_list);
	}
}
		//print_list(token_list);

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;

	if (argc != 1)
		return (1);
	(void)argv;
	g_ms = (t_ms){0};
	copy_envp(envp);
	get_paths(envp);
	token_list = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	create_prompt(&token_list);
	return (0);
}
