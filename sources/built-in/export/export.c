/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:52:15 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/12 21:20:39 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_env(char **env, int nbr_ptr)
{
	int		i;
	char	**aux;

	aux = (char **)ft_calloc(nbr_ptr + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		aux[i] = ft_strdup(env[i]);
		i++;
	}
	return (aux);
}

static int	dup_env(t_token *token_list)
{
	int		i;
	char	**aux;

	aux = copy_env(token_list->ms->env, token_list->ms->env_nbr_ptr);
	free_ptrptr(token_list->ms->env);
	token_list->ms->env = (char **)
		ft_calloc(token_list->ms->env_nbr_ptr + 1, sizeof(char *));
	i = 0;
	while (aux[i])
	{
		token_list->ms->env[i] = ft_strdup(aux[i]);
		i++;
	}
	free_ptrptr(aux);
	return (i);
}

static void	update_env(t_token *token_list, int j)
{
	int	i;

	if (check_if_exists(token_list, j))
		return ;
	token_list->ms->env_nbr_ptr++;
	i = dup_env(token_list);
	token_list->ms->env[i] = ft_strdup(token_list->token[j]);
}

void	export(t_token *token_list)
{
	int	i;

	if (!ft_strncmp(token_list->token[0], "export", 7))
	{
		check_only_export(token_list);
		i = 1;
		while (token_list->token[i])
		{
			if (!check_isname(token_list->token[i]))
			{
				printf("bash: export: '%s': not a valid identifier\n",
					token_list->token[i]);
			}
			else
				update_env(token_list, i);
			i++;
		}
	}
}
