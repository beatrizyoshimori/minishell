/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:21:49 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/14 20:37:04 by lucade-s         ###   ########.fr       */
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

static void	try_find_variable(char **token_i, char **env, int *j)
{
	int		i;
	int		length;

	length = get_length_after_dollar(*token_i, j);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], &(*token_i)[*j - length], length)
			&& env[i][length] == '=')
		{
			found_variable(token_i, env[i], &j, &length);
			break ;
		}
		i++;
	}
	if (!env[i])
		not_found_variable(token_i, &j, &length);
}

static void	try_find_dollar(char **aux_token_i)
{
	int	j;

	j = 0;
	while ((*aux_token_i)[j])
	{
		if ((*aux_token_i)[j] == DOLLAR_VAR)
		{
			if ((*aux_token_i)[j + 1])
				j++;
			if ((*aux_token_i)[j] == '?')
				put_exit_status(g_ms.exit_status, aux_token_i, &j);
			else
				try_find_variable(aux_token_i, g_ms.env, &j);
		}
		if (*aux_token_i)
			j++;
	}
}

void	expand_variable(t_token *token_list)
{
	int		i;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			try_find_dollar(&aux->token[i]);
			i++;
		}
		aux = aux->next;
	}
}
