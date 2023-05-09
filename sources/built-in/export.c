/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:52:15 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/09 19:36:11 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_env(t_ms *ms)
{
	int		i;
	char	**aux;

	aux = (char **)malloc(sizeof(char *) * (ms->env_nbr_ptr + 1));
	aux[ms->env_nbr_ptr] = NULL;
	i = 0;
	while (ms->env[i])
	{
		aux[i] = ft_strdup(ms->env[i]);
		i++;
	}
	return (aux);
}

void	export(t_token *token_list)
{
	int		i;
	char	**aux;

	aux = NULL;
	if (!ft_strncmp((token_list->token)[0], "export", 7)
		&& ft_strchr(token_list->token[1], '=')
		&& token_list->token[1][0] != '=')
	{
		aux = copy_env(token_list->ms);
		token_list->ms->env_nbr_ptr++;
		free_ptrptr(token_list->ms->env);
		token_list->ms->env = (char **)
			malloc(sizeof(char *) * (token_list->ms->env_nbr_ptr + 1));
		token_list->ms->env[token_list->ms->env_nbr_ptr] = NULL;
		i = 0;
		while (aux[i])
		{
			token_list->ms->env[i] = ft_strdup(aux[i]);
			i++;
		}
		token_list->ms->env[i] = ft_strdup(token_list->token[1]);
		free_ptrptr(aux);
	}
}
