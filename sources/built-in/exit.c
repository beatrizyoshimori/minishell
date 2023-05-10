/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:45:45 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/09 22:16:40 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command(t_token *token_list, t_ms *ms)
{
	int					i;
	int					flag;
	long long			exit_status;
	unsigned long long	status;

	i = 0;
	flag = 0;
	status = 0;
	if (!ft_strncmp(token_list->token[0], "exit", 5))
	{
		if (token_list->token[1])
		{
			if (token_list->token[1][0] == '+')
				flag = 1;
			else if (token_list->token[1][0] == '-')
				flag = -1;
			if (flag != 0)
				i++;
			while (ft_isdigit(token_list->token[1][i]))
				i++;
			if (!token_list->token[1][i])
			{
				if (flag != 0)
					status = ft_atoull(token_list->token[1] + 1);
				else
					status = ft_atoull(token_list->token[1]);
			}
			else
				status = (unsigned long long)LL_MAX + 1;
			if ((flag == 1 && status > LL_MAX)
				|| (flag == -1 && status > (unsigned long long)LL_MAX + 1))
				status = (unsigned long long)LL_MAX + 1;
			if (token_list->token[2] && status != (unsigned long long)LL_MAX + 1)
				status = 1;
			else if (status == (unsigned long long)LL_MAX + 1)
			{
				status = 2;
				flag = 1;
			}
		}
		if (flag == -1)
			exit_status = flag * status;
		else
			exit_status = status;
		printf("flag: %i, exit status: %lld, status: %llu\n", flag, exit_status, status);
		if (exit_status != 1)
		{
			printf("exit\n");
			if (exit_status == 2)
				printf("bash: exit: %s: numeric argument required\n", token_list->token[1]);
			rl_clear_history();
			free_token_list(&token_list);
			free_ptrptr(ms->paths);
			free_ptrptr(ms->env);
			free(ms);
			exit(exit_status);
		}
		printf("bash: exit: too many arguments\n");
		return ;
	}
}
