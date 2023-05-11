/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:45:45 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/10 21:27:03 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned long long	check_first_parameter(t_token *token_list, int *f)
{
	int					i;
	unsigned long long	st;

	i = 0;
	st = 0;
	if (token_list->token[1][0] == '+')
		*f = 1;
	else if (token_list->token[1][0] == '-')
		*f = -1;
	if (*f)
		i++;
	while (ft_isdigit(token_list->token[1][i]))
		i++;
	if (!token_list->token[1][i])
	{
		if (*f)
			st = ft_atoull(token_list->token[1] + 1);
		else
			st = ft_atoull(token_list->token[1]);
	}
	else
		st = (unsigned long long)LL_MAX + 2;
	if ((*f != -1 && st > LL_MAX) || st > (unsigned long long)LL_MAX + 1)
		st = (unsigned long long)LL_MAX + 2;
	return (st);
}

static long long	get_exit_status(t_token *token_list)
{
	int					flag;
	unsigned long long	status;

	flag = 0;
	status = 0;
	if (token_list->token[1])
	{
		status = check_first_parameter(token_list, &flag);
		if (token_list->token[2]
			&& status != (unsigned long long)LL_MAX + 2)
			status = 1;
		else if (status == (unsigned long long)LL_MAX + 2)
		{
			status = 2;
			flag = 1;
		}
	}
	if (flag)
		return (flag * status);
	else
		return (status);
}

void	exit_command(t_token *token_list, t_ms *ms)
{
	long long	exit_status;

	exit_status = 0;
	if (!ft_strncmp(token_list->token[0], "exit", 5))
	{
		exit_status = get_exit_status(token_list);
		if (exit_status != 1)
		{
			printf("exit\n");
			if (exit_status == 2)
				printf("bash: exit: %s: numeric argument required\n",
					token_list->token[1]);
			rl_clear_history();
			free_token_list(&token_list);
			free_ptrptr(ms->paths);
			free_ptrptr(ms->env);
			free_ptrptr(ms->env_export);
			free(ms);
			exit(exit_status);
		}
		printf("exit\n");
		printf("bash: exit: too many arguments\n");
		return ;
	}
}
