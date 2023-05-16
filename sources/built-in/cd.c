/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:06:04 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/16 20:02:25 by lucade-s         ###   ########.fr       */
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
	char	*path;

	if (!token[1])
	{
		path = get_home();
		if (!path)
		{
			printf("bilu: cd: HOME not set\n");
			return ;
		}
		if (chdir(path) == -1)
			printf("bilu: cd: %s: %s\n", path, strerror(errno));
	}
	else if (!token[2])
	{
		if (chdir(token[1]) == -1)
			printf("bilu: cd: %s: %s\n", token[1], strerror(errno));
	}
	else
		printf("bilu: cd: too many arguments\n");
}
