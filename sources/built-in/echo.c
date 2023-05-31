/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:10:15 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/31 16:29:05 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_flag(char *token)
{
	int	i;

	i = 0;
	if (token[i] == '-')
	{
		i++;
		while (token[i] == 'n')
			i++;
		if (token[i] == '\0' && i != 1)
			return (1);
	}
	return (0);
}

void	echo(char **token)
{
	int	i;
	int	flag;

	g_ms.exit_status = 0;
	i = 1;
	flag = 0;
	if (token[i] && check_n_flag(token[i]))
	{
		i++;
		flag = 1;
	}
	if (!token[i] && !flag)
		ft_putstr_fd("\n", 1);
	while (token[i])
	{
		ft_putstr_fd(token[i], 1);
		i++;
		if (token[i])
			ft_putstr_fd(" ", 1);
		else if (!flag)
			ft_putstr_fd("\n", 1);
	}
}
