/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:27:18 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/17 14:01:16 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_ctrl_d(char *prompt)
{
	if (!prompt)
	{
		if (!g_ms.on_fork)
			printf("exit");
		printf("\n");
		free(g_ms.pipe_fd);
		free(g_ms.pid);
		free_ptrptr(g_ms.env);
		free(g_ms.home);
		rl_clear_history();
		exit (0);
	}
}

static int	check_only_whitespaces(char **prompt)
{
	int	i;

	i = 0;
	while ((*prompt)[i])
	{
		while (ft_iswhitespace((*prompt)[i]))
			i++;
		if (!(*prompt)[i])
			return (1);
		else
			break ;
	}
	return (0);
}

void	check_whitespaces_enter(char **prompt)
{
	while (!(**prompt) || check_only_whitespaces(prompt))
	{
		if (**prompt)
			add_history(*prompt);
		free(*prompt);
		*prompt = readline("bilu> ");
	}
}

void	lexer(char **prompt)
{
	mark_metachar_inside_quotes(*prompt);
	find_metachar(*prompt);
	create_spaces(prompt);
	mark_pipe_spaces(*prompt);
	mark_token_spaces(*prompt);
	change_metachar_back(*prompt);
}
