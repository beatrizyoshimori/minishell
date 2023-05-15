/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:52:15 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/15 19:25:02 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_env(void)
{
	int		i;
	char	**aux;

	aux = (char **)ft_calloc(g_ms.env_nbr_ptr + 1, sizeof(char *));
	i = 0;
	while (g_ms.env[i])
	{
		aux[i] = ft_strdup(g_ms.env[i]);
		i++;
	}
	return (aux);
}

static int	dup_env(void)
{
	int		i;
	char	**aux;

	aux = copy_env();
	free_ptrptr(g_ms.env);
	g_ms.env = (char **)
		ft_calloc(g_ms.env_nbr_ptr + 1, sizeof(char *));
	i = 0;
	while (aux[i])
	{
		g_ms.env[i] = ft_strdup(aux[i]);
		i++;
	}
	free_ptrptr(aux);
	return (i);
}

static void	update_env(char **token, int j)
{
	int	i;

	if (check_if_exists_exp(token, j))
		return ;
	g_ms.env_nbr_ptr++;
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
			printf("bash: export: '%s': not a valid identifier\n", token[i]);
		else
			update_env(token, i);
		i++;
	}
}
