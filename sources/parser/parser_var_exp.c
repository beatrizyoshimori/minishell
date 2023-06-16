/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:21:49 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/16 18:12:28 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_exit_status(char **token_i, int *j)
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
	*j = length - 1;
	free(aux);
}

void	try_find_variable(char **token_i, int *j)
{
	int	i;
	int	length;
	int	isname;

	i = 0;
	length = 0;
	isname = get_length_after_dollar(*token_i, j, &length);
	if (isname == 1)
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

static void	try_find_dollar(char **token_i)
{
	int	j;

	j = 0;
	while ((*token_i)[j])
	{
		if ((*token_i)[j] == DOLLAR_VAR)
		{
			if ((*token_i)[j + 1])
				j++;
			if ((*token_i)[j] == '?')
				put_exit_status(token_i, &j);
			else
				try_find_variable(token_i, &j);
		}
		if (*token_i)
			j++;
	}
}

static void	check_empty_string(char **token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i])
	{
		if (!token[i][0])
		{
			j = i + 1;
			while (token[j])
			{
				free(token[j - 1]);
				token[j - 1] = ft_strdup(token[j]);
				j++;
			}
			free(token[j - 1]);
			token[j - 1] = NULL;
			i--;
		}
		i++;
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
			if (i == 0 || (i > 0 && ft_strncmp(aux->token[i - 1], "<<", 3)))
				try_find_dollar(&aux->token[i]);
			j = 0;
			while (aux->token[i][j])
			{
				if (aux->token[i][j] == DOLLAR_VAR)
					aux->token[i][j] = '$';
				j++;
			}
			try_find_tilde(&aux->token[i]);
			i++;
		}
		check_empty_string(aux->token);
		aux = aux->next;
	}
}
