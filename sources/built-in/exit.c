/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:45:45 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/09 19:37:53 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command(t_token *token_list, t_ms *ms)
{
	if (ft_strncmp(token_list->token[0], "exit", 5) == 0)
	{
		rl_clear_history();
		free_token_list(&token_list);
		free_ptrptr(ms->paths);
		free_ptrptr(ms->env);
		free(ms);
		exit(0);
	}
}
