/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:04:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/10 22:30:42 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_program(t_token **token_list, t_ms *ms)
{
	rl_clear_history();
	free_ptrptr(ms->paths);
	free_ptrptr(ms->env);
	free_ptrptr(ms->env_export);
	free(ms);
	free_token_list(token_list);
	exit(1);
}
