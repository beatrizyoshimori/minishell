/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:06:04 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/15 21:49:15 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home(void)
{
	int	i;

	i = 0;
	while (g_ms.env[i])
	{
		if (!ft_strncmp(g_ms.env[i], "HOME=", 5))
			return (g_ms.env[i] + 5);
		i++;
	}
	return (NULL);
}

void	cd(char **token)
{
	if (!token[1])
	{
		chdir(get_home());
	}
}
