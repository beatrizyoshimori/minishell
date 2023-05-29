/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:52:49 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/29 18:33:41 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd_builtin(int redirect, int fd[2])
{
	if (redirect % REDIRECT_INPUT == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
	if (redirect % REDIRECT_OUTPUT == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
}

void	change_fd_back(int redirect)
{
	if (redirect % REDIRECT_INPUT == 0)
		dup2(g_ms.backup_fd[0], 0);
	if (redirect % REDIRECT_OUTPUT == 0)
		dup2(g_ms.backup_fd[1], 1);
}
