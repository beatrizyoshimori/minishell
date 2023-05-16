/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:04:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/16 18:32:31 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_program(t_token **token_list)
{
	rl_clear_history();
	free_ptrptr(g_ms.paths);
	free_ptrptr(g_ms.env);
	free(g_ms.home);
	free_token_list(token_list);
	exit(1);
}
