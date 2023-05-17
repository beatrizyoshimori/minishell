/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:52:15 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/17 18:39:33 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(char **token, int j)
{
	int	i;

	if (check_if_exists_exp(token, j))
		return ;
	i = dup_env();
	g_ms.env[i] = ft_strdup(token[j]);
}

void	export(char **token)
{
	int	i;

	check_only_export(token);
	i = 1;
	while (token[i])
	{
		if (!check_isname_exp(token[i]))
			printf("bilu: export: '%s': not a valid identifier\n", token[i]);
		else
			update_env(token, i);
		i++;
	}
}
