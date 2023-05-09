/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:10:15 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/08 20:51:47 by byoshimo         ###   ########.fr       */
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
	if (ft_strncmp((token_list->token)[i], "echo", 5) == 0)
	{
			i++;
		if (check_n_flag(token_list->token[i]))
		{
			i++;
			flag = 1;
		}
		while ((token_list->token)[i])
		{
			printf("%s", (token_list->token)[i]);
			i++;
			if ((token_list->token)[i])
				printf(" ");
			else if (!flag)
				printf("\n");
		}
	}
}
