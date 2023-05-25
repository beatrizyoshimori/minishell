/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:06:04 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/25 20:09:13 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_parameter_update(char *old_pwd, char *new_pwd, int dash)
{
	new_pwd = getcwd(NULL, 0);
	if (dash)
	{
		ft_putstr_fd(new_pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	update_pwd_or_oldpwd(new_pwd, "PWD=", 4);
	update_pwd_or_oldpwd(old_pwd, "OLDPWD=", 7);
	free(new_pwd);
}

static void	print_error_cd(char *token_i)
{
	ft_putstr_fd("bilu: cd:", 2);
	ft_putstr_fd(token_i, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

static void	cd_parameter(char **token, char *old_pwd)
{
	int		dash;
	char	*new_pwd;

	dash = 0;
	new_pwd = NULL;
	if (!ft_strncmp(token[1], "-", 2))
	{
		dash = 1;
		new_pwd = get_path("OLDPWD=", 7);
		if (!new_pwd)
		{
			ft_putstr_fd("bilu: cd: OLDPWD not set\n", 2);
			g_ms.exit_status = 1;
			return ;
		}
		free(token[1]);
		token[1] = ft_strdup(new_pwd);
	}
	if (chdir(token[1]) == -1)
	{
		print_error_cd(token[1]);
		g_ms.exit_status = 1;
	}
	else
		cd_parameter_update(old_pwd, new_pwd, dash);
}

static void	cd_home(char *old_pwd)
{
	char	*new_pwd;

	new_pwd = get_path("HOME=", 5);
	if (!new_pwd)
	{
		ft_putstr_fd("bilu: cd: HOME not set\n", 2);
		g_ms.exit_status = 1;
		return ;
	}
	if (chdir(new_pwd) == -1)
	{
		ft_putstr_fd("bilu: cd:", 2);
		ft_putstr_fd(new_pwd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_ms.exit_status = 1;
	}
	else
	{
		update_pwd_or_oldpwd(new_pwd, "PWD=", 4);
		update_pwd_or_oldpwd(old_pwd, "OLDPWD=", 7);
	}
}

void	cd(char **token)
{
	char	*old_pwd;

	g_ms.exit_status = 0;
	old_pwd = getcwd(NULL, 0);
	if (!token[1] || !ft_strncmp(token[1], "--", 3))
		cd_home(old_pwd);
	else if (!token[2])
		cd_parameter(token, old_pwd);
	else
	{
		ft_putstr_fd("bilu: cd: too many arguments\n", 2);
		g_ms.exit_status = 1;
	}
	free(old_pwd);
}
