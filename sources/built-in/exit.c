/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:45:45 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/30 19:55:45 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long long	check_first_parameter(char **token, int *f)
{
	int					i;
	unsigned long long	st;

	i = 0;
	st = 0;
	if (token[1][0] == '+')
		*f = 1;
	else if (token[1][0] == '-')
		*f = -1;
	if (*f)
		i++;
	while (ft_isdigit(token[1][i]))
		i++;
	if (!token[1][i])
	{
		if (*f)
			st = ft_atoull(token[1] + 1);
		else
			st = ft_atoull(token[1]);
	}
	else
		st = (unsigned long long)LL_MAX + 2;
	if ((*f != -1 && st > LL_MAX) || st > (unsigned long long)LL_MAX + 1)
		st = (unsigned long long)LL_MAX + 2;
	return (st);
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
		rl_clear_history();
		free_token_list(&token_list);
		free(g_ms.pipe_fd);
		free(g_ms.pid);
		free_ptrptr(g_ms.paths);
		free_ptrptr(g_ms.env);
		free(g_ms.home);
		exit(g_ms.exit_status);
	}
	if (!g_ms.on_fork)
		ft_putstr_fd("exit\n", 1);
	print_error("bilu: ", "exit", "too many arguments", 1);
	return ;
}
