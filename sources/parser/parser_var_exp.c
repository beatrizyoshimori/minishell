/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:21:49 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/17 16:13:22 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_exit_status(char **token_i, int *j)
{
	int		length;
	char	*exit_st;
	char	*aux;

	(*j)++;
	exit_st = ft_itoa(g_ms.exit_status);
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

static void	try_find_variable(char **token_i, int *j)
{
	int	i;
	int	length;
	int	isname;

	i = 0;
	length = 0;
	isname = get_length_after_dollar(*token_i, j, &length);
	if (isname)
	{
		while (g_ms.env[i])
		{
			if (!ft_strncmp(g_ms.env[i], &(*token_i)[*j - length], length)
				&& g_ms.env[i][length] == '=')
			{
				found_variable(token_i, g_ms.env[i], j, &length);
				break ;
			}
			i++;
		}
	}
	if (!g_ms.env[i] || !isname)
		not_found_variable(token_i, j, &length);
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
				put_exit_status(aux_token_i, &j);
			else
				try_find_variable(aux_token_i, &j);
		}
		if (*aux_token_i)
			j++;
	}
}

void	expand_variable(t_token *token_list)
{
	int		i;
	int		exp;
	t_token	*aux;

	exp = 0;
	aux = token_list;
	while (aux)
	{
		if (!ft_strncmp(aux->token[0], "export", 7))
			exp = 1;
		i = 0;
		while (aux->token[i])
		{
			try_find_dollar(&aux->token[i]);
			try_find_tilde(&aux->token[i]);
			i++;
		}
		aux = aux->next;
	}
}
