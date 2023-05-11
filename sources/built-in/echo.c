/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:10:15 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/10 18:46:35 by lucade-s         ###   ########.fr       */
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
		if (token[i] == '\0')
			return (1);
	}
	return (0);
}

void	echo(t_token *token_list)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!ft_strncmp(token_list->token[i], "echo", 5))
	{
		i++;
		if (token_list->token[i] && check_n_flag(token_list->token[i]))
		{
			i++;
			flag = 1;
		}
		if (!token_list->token[i] && !flag)
			printf("\n");
		while (token_list->token[i])
		{
			printf("%s", token_list->token[i]);
			i++;
			if (token_list->token[i])
				printf(" ");
			else if (!flag)
				printf("\n");
		}
	}
}
