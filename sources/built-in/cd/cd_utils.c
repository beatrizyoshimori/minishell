/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:18:35 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/18 18:27:54 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_or_oldpwd(char *pwd, char *variable, int length)
{
	int	i;

	i = 0;
	while (g_ms.env[i])
	{
		if (!ft_strncmp(g_ms.env[i], variable, length))
		{
			free(g_ms.env[i]);
			g_ms.env[i] = ft_strjoin(variable, pwd);
			return ;
		}
		i++;
	}
	i = dup_env();
	g_ms.env[i] = ft_strjoin(variable, pwd);
}

char	*get_path(char *variable, int length)
{
	int	i;

	i = 0;
	while (g_ms.env[i])
	{
		if (!ft_strncmp(g_ms.env[i], variable, length))
			return (g_ms.env[i] + length);
		i++;
	}
	return (NULL);
}
