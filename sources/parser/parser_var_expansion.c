/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:21:49 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/13 19:38:52 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_exit_status(int exit_status, char **token_i, int *j)
{
	int		length;
	char	*exit_st;
	char	*aux;

	(*j)++;
	exit_st = ft_itoa(exit_status);
	length = ft_strlen(exit_st);
	aux = (char *)ft_calloc(ft_strlen(*token_i)
			+ length - 1, sizeof(char));
	ft_strlcpy(aux, *token_i, *j - 1);
	ft_strlcpy(&aux[*j - 2], exit_st, length + 1);
	ft_strlcpy(&aux[*j + length - 2],
		&(*token_i)[*j], ft_strlen(*token_i) - *j + 1);
	free(exit_st);
	free(*token_i);
	*token_i = ft_strdup(aux);
	*j -= length + 1;
	free(aux);
}

static void	get_variable_name(char **token_i, char **env, int *j)
{
	int		i;
	int		length;
	char	*aux;

	length = 0;
	while ((*token_i)[*j] == '_' || ft_isalnum((*token_i)[*j]))
	{
		length++;
		(*j)++;
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], &(*token_i)[*j - length], length)
			&& env[i][length] == '=')
		{
			aux = (char *)ft_calloc(ft_strlen(*token_i)
					+ ft_strlen(env[i]), sizeof(char));
			ft_strlcpy(aux, *token_i, *j - length);
			ft_strlcpy(&aux[*j - length - 1], &env[i][length + 1],
				ft_strlen(env[i]) - length);
			ft_strlcpy(&aux[*j - 2 * length + ft_strlen(env[i]) - 2],
				&(*token_i)[*j], ft_strlen(*token_i) - *j + 1);
			free(*token_i);
			*token_i = ft_strdup(aux);
			*j = *j + ft_strlen(env[i]) - 2 * (length + 1) - 1;
			free(aux);
			break ;
		}
		i++;
	}
	if (!env[i])
	{
		aux = (char *)ft_calloc(ft_strlen(*token_i), sizeof(char));
		ft_strlcpy(aux, *token_i, *j - length);
		ft_strlcpy(&aux[*j - length - 1],
			&(*token_i)[*j], ft_strlen(*token_i) - *j + 1);
		free(*token_i);
		*token_i = ft_strdup(aux);
		*j = *j - length - 2;
		free(aux);
	}
}

void	expand_variable(t_token *token_list)
{
	int		i;
	int		j;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			j = 0;
			while (aux->token[i][j])
			{
				if (aux->token[i][j] == DOLLAR_VAR)
				{
					if (aux->token[i][j + 1])
					{
						j++;
						if (aux->token[i][j] == DOLLAR_VAR)
							j--;
					}
					if (aux->token[i][j] == '_' || ft_isalpha(aux->token[i][j]))
						get_variable_name(&aux->token[i], aux->ms->env, &j);
					else if (aux->token[i][j] == '?')
						put_exit_status(token_list->ms->exit_status,
							&aux->token[i], &j);
				}
				if (aux->token[i])
					j++;
			}
			i++;
		}
		aux = aux->next;
	}
}
