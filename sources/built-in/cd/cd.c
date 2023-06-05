/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:06:04 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/05 15:20:44 by lucade-s         ###   ########.fr       */
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
			print_error("bilu: ", "cd", "OLDPWD not set", 1);
			return ;
		}
		free(token[1]);
		token[1] = ft_strdup(new_pwd);
	}
	if (chdir(token[1]) == -1)
	{
		if (!token[1][0])
			return ;
		print_error("bilu: cd: ", token[1], strerror(errno), 1);
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
		print_error("bilu: ", "cd", "HOME not set", 1);
		return ;
	}
	if (chdir(new_pwd) == -1)
		print_error("bilu: cd: ", new_pwd, strerror(errno), 1);
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
		print_error("bilu: ", "cd", "too many arguments", 1);
	free(old_pwd);
}
