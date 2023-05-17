/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:06:04 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/17 20:10:00 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd_or_oldpwd(char *pwd, char *variable, int length)
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

static char	*get_path(char *variable, int length)
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

static void	cd_parameter(char **token, char *new_pwd, char *old_pwd, int *dash)
{
	if (!ft_strncmp(token[1], "-", 2))
	{
		*dash = 1;
		new_pwd = get_path("OLDPWD=", 7);
		if (!new_pwd)
		{
			printf("bilu: cd: OLDPWD not set\n");
			return ;
		}
		free(token[1]);
		token[1] = ft_strdup(new_pwd);
	}
	if (chdir(token[1]) == -1)
		printf("bilu: cd: %s: %s\n", token[1], strerror(errno));
	else
	{
		new_pwd = getcwd(NULL, 0);
		if (*dash)
			printf("%s\n", new_pwd);
		update_pwd_or_oldpwd(new_pwd, "PWD=", 4);
		update_pwd_or_oldpwd(old_pwd, "OLDPWD=", 7);
		free(new_pwd);
	}
}

static void	cd_home(char *old_pwd)
{
	char	*new_pwd;

	new_pwd = get_path("HOME=", 5);
	if (!new_pwd)
	{
		printf("bilu: cd: HOME not set\n");
		return ;
	}
	if (chdir(new_pwd) == -1)
		printf("bilu: cd: %s: %s\n", new_pwd, strerror(errno));
	else
	{
		update_pwd_or_oldpwd(new_pwd, "PWD=", 4);
		update_pwd_or_oldpwd(old_pwd, "OLDPWD=", 7);
	}
}

void	cd(char **token)
{
	int		dash;
	char	*new_pwd;
	char	*old_pwd;

	dash = 0;
	new_pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!token[1] || !ft_strncmp(token[1], "--", 3))
		cd_home(old_pwd);
	else if (!token[2])
		cd_parameter(token, new_pwd, old_pwd, &dash);
	else
		printf("bilu: cd: too many arguments\n");
	free(old_pwd);
}
