/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:37:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/08 21:58:25 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_token *token_list)
{
	int	i;

	if (!ft_strncmp((token_list->token)[0], "env", 4) && !token_list->token[1])
	{
		i = 0;
		while (token_list->ms->env[i])
		{
			printf("%s\n", token_list->ms->env[i]);
			i++;
		}
	}
}
