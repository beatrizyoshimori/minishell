/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:04:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/13 13:16:48 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_program(t_token **token_list, t_ms *ms)
{
	rl_clear_history();
	free_ptrptr(ms->paths);
	free_ptrptr(ms->env);
	free(ms);
	free_token_list(token_list);
	exit(1);
}
