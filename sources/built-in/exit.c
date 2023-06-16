/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:45:45 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/16 16:37:53 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long long	check_first_parameter(char **token, int *flag)
{
	int					i;
	unsigned long long	status;

	i = 0;
	status = 0;
	if (!token[1][0])
		status = (unsigned long long)LL_MAX + 2;
	else
	{
		while ((token[1][i] >= 9 && token[1][i] <= 13) || token[1][i] == 32)
			i++;
		if (token[1][i] == '+')
			*flag = 1;
		else if (token[1][i] == '-')
			*flag = -1;
		status = ft_atoull(token[1]);
	}
	return (status);
}

static long long	get_exit_status(char **token, int *ver)
{
	int					flag;
	unsigned long long	status;

	flag = 0;
	status = 0;
	if (token[1])
	{
		status = check_first_parameter(token, &flag);
		if (token[2] && status != (unsigned long long)LL_MAX + 2)
		{
			*ver = 1;
			status = 1;
		}
		else if (status == (unsigned long long)LL_MAX + 2)
		{
			*ver = 2;
			status = 2;
			flag = 1;
		}
	}
	if (flag)
		return (flag * status);
	else
		return (status);
}

void	exit_command(t_token *token_list, char **token)
{
	int	ver;

	ver = 0;
	g_ms.exit_status = get_exit_status(token, &ver);
	if (ver != 1)
	{
		if (!g_ms.on_fork)
			ft_putstr_fd("exit\n", 1);
		if (ver == 2)
			print_error("bilu: exit: ", token[1],
				"numeric argument required", 2);
		exit_process(token_list);
	}
	if (!g_ms.on_fork)
		ft_putstr_fd("exit\n", 1);
	print_error("bilu: ", "exit", "too many arguments", 1);
	return ;
}
