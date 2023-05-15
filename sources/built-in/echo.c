/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:10:15 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/15 16:31:10 by lucade-s         ###   ########.fr       */
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

void	echo(char **token)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (token[i] && check_n_flag(token[i]))
	{
		i++;
		flag = 1;
	}
	if (!token[i] && !flag)
		printf("\n");
	while (token[i])
	{
		printf("%s", token[i]);
		i++;
		if (token[i])
			printf(" ");
		else if (!flag)
			printf("\n");
	}
}
