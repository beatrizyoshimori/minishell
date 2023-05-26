/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:15:08 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/26 16:47:40 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*pwd;

	g_ms.exit_status = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("bilu: pwd: ", 2);
		ft_putstr_fd(pwd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_ms.exit_status = 1;
	}
	else
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	free(pwd);
}
