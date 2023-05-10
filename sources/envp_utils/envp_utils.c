/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:12:43 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/09 19:13:52 by lucade-s         ###   ########.fr       */
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
	ms->env = (char **)malloc(sizeof(char *) * (i + 1));
	ms->env[i] = NULL;
	i = 0;
	while (envp[i])
	{
		ms->env[i] = ft_strdup(envp[i]);
		i++;
	}
}