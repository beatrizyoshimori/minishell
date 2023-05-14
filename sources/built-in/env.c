/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:37:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/14 20:27:36 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_token *token_list)
{
	int	i;

	if (!ft_strncmp(token_list->token[0], "env", 4) && !token_list->token[1])
	{
		i = 0;
		while (g_ms.env[i])
		{
			if (ft_strchr(g_ms.env[i], '='))
				printf("%s\n", g_ms.env[i]);
			i++;
		}
	}
	else if (!ft_strncmp(token_list->token[0], "env", 4))
		printf("env: '%s': No such file or directory\n", token_list->token[1]);
}
