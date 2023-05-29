/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/29 20:37:37 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	g_ms;

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	exec_command(t_token *token_list)
{
	if (g_ms.num_tokens == 1 && !token_list->no_exec)
	{
		if (ft_isbuiltin(token_list))
			exec_builtin(token_list);
		else
			start_processes(token_list);
	}
	else if (g_ms.num_tokens > 1)
		start_processes(token_list);
}

static void	create_prompt(t_token **token_list)
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
		if ((*token_list)->token[0])
			exec_command(*token_list);
		free_token_list(token_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;

	if (argc != 1)
		return (1);
	(void)argv;
	g_ms = (t_ms){0};
	g_ms.backup_fd[0] = dup(0);
	g_ms.backup_fd[1] = dup(1);
	copy_envp(envp);
	get_paths(envp);
	token_list = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	create_prompt(&token_list);
	return (0);
}
