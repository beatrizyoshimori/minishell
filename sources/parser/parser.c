/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:57:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/05 20:41:14 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_pipe_error(t_token **token_list, t_ms *ms)
{
	t_token	*aux;

	aux = *token_list;
	if (aux->token[0][0] == '|')
		print_syntax_error(token_list, ms, '|');
	while (aux)
	{
		if (aux->token[0][0] == '|'
			&& (aux->next == NULL || aux->next->token[0][0] == '|'))
			print_syntax_error(token_list, ms, '|');
		aux = aux->next;
	}
}

static void	check_redirections_error(t_token **token_list, t_ms *ms)
{
	int		i;
	t_token	*aux;

	aux = *token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			if (aux->token[i][0] == '<' || aux->token[i][0] == '>')
			{
				i++;
				if (aux->token[i] == NULL)
					print_syntax_error(token_list, ms, '\n');
				else if (aux->token[i][0] == '<' || aux->token[i][0] == '>'
					|| aux->token[i][0] == '|')
					print_syntax_error(token_list, ms, aux->token[i][0]);
			}
			i++;
		}
		aux = aux->next;
	}
}

static void	aux_check_quotes(t_token **token_list, t_ms *ms, char *a, int *j)
{
	char	c;

	while (a[*j])
	{
		c = a[*j];
		if (c == '\'' || c == '\"')
		{
			(*j)++;
			while (a[*j] && a[*j] != c)
				(*j)++;
			if (a[*j] == '\0')
				print_syntax_error(token_list, ms, '\n');
		}
		(*j)++;
	}
}

static void	check_quotes_error(t_token **token_list, t_ms *ms)
{
	int		i;
	int		j;
	t_token	*aux;

	aux = *token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			j = 0;
			aux_check_quotes(token_list, ms, aux->token[i], &j);
			i++;
		}
		aux = aux->next;
	}
}

void	parser(t_token **token_list, t_ms *ms)
{
	check_pipe_error(token_list, ms);
	check_redirections_error(token_list, ms);
	check_quotes_error(token_list, ms);
}
