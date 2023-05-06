/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:04:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/05 20:39:40 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command(char *prompt, t_ms *ms)
{
	if (!ft_strncmp(prompt, "exit", 5))
	{
		rl_clear_history();
		free_split(ms->paths);
		free(ms);
		free(prompt);
		exit(0);
	}
}

void	exit_program(t_token **token_list, t_ms *ms)
{
	rl_clear_history();
	free_split(ms->paths);
	free(ms);
	free_token_list(token_list);
	exit(1);
}
