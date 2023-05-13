/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:12:43 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/13 13:17:39 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_paths(char **envp, t_ms *ms)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	ms->paths = ft_split(envp[i] + 5, ':');
}

void	copy_envp(char **envp, t_ms *ms)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	ms->env_nbr_ptr = i;
	ms->env = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		ms->env[i] = ft_strdup(envp[i]);
		i++;
	}
}
