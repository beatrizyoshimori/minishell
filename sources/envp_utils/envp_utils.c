/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:12:43 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/16 16:55:36 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_env(void)
{
	int		i;
	char	**aux;

	aux = (char **)ft_calloc(g_ms.env_nbr_ptr + 1, sizeof(char *));
	i = 0;
	while (g_ms.env[i])
	{
		aux[i] = ft_strdup(g_ms.env[i]);
		i++;
	}
	return (aux);
}

int	dup_env(void)
{
	int		i;
	char	**aux;

	aux = copy_env();
	free_ptrptr(g_ms.env);
	g_ms.env_nbr_ptr++;
	g_ms.env = (char **)
		ft_calloc(g_ms.env_nbr_ptr + 1, sizeof(char *));
	i = 0;
	while (aux[i])
	{
		g_ms.env[i] = ft_strdup(aux[i]);
		i++;
	}
	free_ptrptr(aux);
	return (i);
}

void	get_paths(void)
{
	int	i;

	i = 0;
	while (g_ms.env[i])
	{
		if (!ft_strncmp(g_ms.env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!g_ms.env[i])
		g_ms.paths = NULL;
	else
		g_ms.paths = ft_split(g_ms.env[i] + 5, ':');
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
