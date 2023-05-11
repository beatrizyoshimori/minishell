/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:20:17 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/10 22:22:38 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(t_ms *ms)
{
	int		i;
	char	**aux;

	aux = (char **)ft_calloc(ms->env_nbr_ptr + 1, sizeof(char *));
	i = 0;
	while (ms->env[i])
	{
		aux[i] = ft_strdup(ms->env[i]);
		i++;
	}
	return (aux);
}
