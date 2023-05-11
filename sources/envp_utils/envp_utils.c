/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:12:43 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/10 22:24:01 by lucade-s         ###   ########.fr       */
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

char	*copy_env_export(char *envp_i)
{
	int		j;
	char	*env_export_i;

	j = ft_strlen(envp_i);
	if (ft_strchr(envp_i, '='))
		j += 2;
	env_export_i = (char *)ft_calloc(j + 1, sizeof(char));
	j = 0;
	while (envp_i[j] && envp_i[j] != '=')
	{
		env_export_i[j] = envp_i[j];
		j++;
	}
	if (envp_i[j] != '=')
		return (env_export_i);
	env_export_i[j] = envp_i[j];
	env_export_i[j + 1] = '\"';
	j += 2;
	while (envp_i[j - 1])
	{
		env_export_i[j] = envp_i[j - 1];
		j++;
	}
	env_export_i[j] = '\"';
	return (env_export_i);
}

void	copy_envp(char **envp, t_ms *ms)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	ms->env_nbr_ptr = i;
	ms->env_exp_nbr_ptr = i;
	ms->env = (char **)ft_calloc(i + 1, sizeof(char *));
	ms->env_export = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		ms->env[i] = ft_strdup(envp[i]);
		ms->env_export[i] = copy_env_export(envp[i]);
		i++;
	}
}
