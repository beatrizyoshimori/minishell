/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:37:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/03 12:59:02 by byoshimo         ###   ########.fr       */
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
	else
		print_error("bilu: env: ", token[1], "No such file or directory", 127);
}
