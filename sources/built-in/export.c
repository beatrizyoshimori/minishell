/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:52:15 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/10 22:19:55 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_isname(char *env_i)
{
	int	j;

	j = 0;
	if (env_i[j] != '_' && !ft_isalpha(env_i[j]))
		return (0);
	j++;
	while ((env_i[j] == '_' || ft_isalnum(env_i[j])) && env_i[j] != '=')
		j++;
	if (!env_i[j] || env_i[j] == '=')
		return (1);
	return (0);
}

static int	dup_envs(t_token *token_list)
{
	int		i;
	char	**aux;

	aux = copy_env(token_list->ms);
	free_ptrptr(token_list->ms->env);
	free_ptrptr(token_list->ms->env_export);
	token_list->ms->env = (char **)
		ft_calloc(token_list->ms->env_nbr_ptr + 1, sizeof(char *));
	token_list->ms->env_export = (char **)
		ft_calloc(token_list->ms->env_exp_nbr_ptr + 1, sizeof(char *));
	i = 0;
	while (aux[i])
	{
		token_list->ms->env[i] = ft_strdup(aux[i]);
		token_list->ms->env_export[i] = copy_env_export(aux[i]);
		i++;
	}
	free_ptrptr(aux);
	return (i);
}

static void	update_envs(t_token *token_list, int j)
{
	int	i;

	i = dup_envs(token_list);
	if (ft_strchr(token_list->token[j], '=')
		&& check_isname(token_list->token[j]))
	{
		token_list->ms->env[i] = ft_strdup(token_list->token[j]);
		token_list->ms->env_export[i] = copy_env_export(token_list->token[j]);
	}
	else if (check_isname(token_list->token[j]))
		token_list->ms->env_export[i] = copy_env_export(token_list->token[j]);
}

static void	check_only_export(t_token *token_list)
{
	int	i;

	if (!token_list->token[1])
	{
		i = 0;
		while (token_list->ms->env_export[i])
		{
			printf("declare -x %s\n", token_list->ms->env_export[i]);
			i++;
		}
		return ;
	}
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
				i++;
			}
			else
			{
				token_list->ms->env_exp_nbr_ptr++;
				if (ft_strchr(token_list->token[i], '='))
					token_list->ms->env_nbr_ptr++;
				update_envs(token_list, i);
			}
			i++;
		}
	}
}
