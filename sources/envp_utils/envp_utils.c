/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:12:43 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/16 19:17:29 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	g_ms.paths = ft_split(envp[i] + 5, ':');
}

void	copy_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_ms.env_nbr_ptr = i;
	g_ms.env = (char **)ft_calloc(i + 1, sizeof(char *));
	g_ms.home = (char *)ft_calloc(1, sizeof(char));
	i = 0;
	while (envp[i])
	{
		g_ms.env[i] = ft_strdup(envp[i]);
		if (!ft_strncmp(envp[i], "HOME=", 5))
		{
			free(g_ms.home);
			g_ms.home = ft_strdup(envp[i] + 5);
		}
		i++;
	}
}
