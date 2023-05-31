/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:30:57 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/31 19:21:45 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipe_error(t_token *token_list)
{
	t_token	*aux;

	aux = token_list;
	if (aux->token[0][0] == '|')
	{
		print_syntax_error("|");
		return ;
	}
	while (aux)
	{
		if (aux->token[0][0] == '|'
			&& (aux->next == NULL || aux->next->token[0][0] == '|'))
		{
			print_syntax_error("|");
			return ;
		}
		aux = aux->next;
	}
}

void	print_syntax_error(char *c)
{
	ft_putstr_fd("bilu: syntax error near unexpected token ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_ms.syntax_error = 1;
	g_ms.exit_status = 2;
}

void	remove_quotes_aux(char **token_i)
{
	int		i;
	char	*aux;
	char	**split;

	split = ft_split(*token_i, REMOVE_QUOTES);
	if (!split[0])
	{
		free_ptrptr(split);
		free(*token_i);
		*token_i = (char *)ft_calloc(1, sizeof(char));
		return ;
	}
	aux = (char *)ft_calloc(1, sizeof(char));
	i = 0;
	while (split[i])
	{
		free(*token_i);
		*token_i = ft_strjoin(aux, split[i]);
		free(aux);
		aux = ft_strdup(*token_i);
		i++;
	}
	free(aux);
	free_ptrptr(split);
}

void	mark_quotes(char **token_i, int *j)
{
	char	c;

	c = (*token_i)[*j];
	(*token_i)[*j] = REMOVE_QUOTES;
	while ((*token_i)[*j] != c)
		(*j)++;
	(*token_i)[*j] = REMOVE_QUOTES;
}

void	remove_quotes(t_token *token_list)
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
				if (aux->token[i][j] == '\'' || aux->token[i][j] == '\"')
					mark_quotes(&aux->token[i], &j);
				j++;
			}
			remove_quotes_aux(&aux->token[i]);
			i++;
		}
		aux = aux->next;
	}
}
