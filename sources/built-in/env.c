/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:37:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/26 16:47:29 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **token)
{
	int	i;

	g_ms.exit_status = 0;
	if (!token[1])
	{
		i = 0;
		while (g_ms.env[i])
		{
			if (ft_strchr(g_ms.env[i], '='))
			{
				ft_putstr_fd(g_ms.env[i], 1);
				ft_putstr_fd("\n", 1);
			}
			i++;
		}
	}
	else if (!ft_strncmp(token[0], "env", 4))
	{
		ft_putstr_fd("bilu: env: ", 2);
		ft_putstr_fd(token[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		g_ms.exit_status = 127;
	}
}
