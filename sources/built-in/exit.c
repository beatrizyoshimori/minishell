/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:45:45 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/08 22:00:54 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command(t_token *token_list, t_ms *ms)
{
	if (ft_strncmp((token_list->token)[0], "exit", 5) == 0)
	{
		rl_clear_history();
		free_token_list(&token_list);
		free_ptrptr(ms->paths);
		free_ptrptr(ms->env);
		free(ms);
		exit(0);
	}
}