/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:07:38 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/15 20:04:43 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_isname_unset(char *token_i)
{
	int	j;

	j = 0;
	if (token_i[j] != '_' && !ft_isalpha(token_i[j]))
		return (0);
	j++;
	while (token_i[j] == '_' || ft_isalnum(token_i[j]))
		j++;
	if (!token_i[j])
		return (1);
	return (0);
}

static void	remove_env_i(int j)
{
	while (g_ms.env[j])
	{
		free(g_ms.env[j]);
		g_ms.env[j] = ft_strdup(g_ms.env[j + 1]);
		if (!g_ms.env[j][0])
		{
			free(g_ms.env[j]);
			g_ms.env[j] = NULL;
		}
		j++;
	}
}

static int	remove_if_exists(char *token_i, int j, int length)
{
	if (!ft_strncmp(g_ms.env[j], token_i, length)
		&& (!g_ms.env[j][length] || g_ms.env[j][length] == '='))
	{
		remove_env_i(j);
		return (1);
	}
	return (0);
}

void	unset(char **token)
{
	int	i;
	int	j;
	int	length;

	if (!token[1])
		return ;
	i = 1;
	while (token[i])
	{
		if (!check_isname_unset(token[i]))
			printf("bash: export: '%s': not a valid identifier\n", token[i]);
		else
		{
			j = 0;
			length = ft_strlen(token[i]);
			while (g_ms.env[j])
			{
				if (remove_if_exists(token[i], j, length))
					break ;
				j++;
			}
		}
		i++;
	}
}
