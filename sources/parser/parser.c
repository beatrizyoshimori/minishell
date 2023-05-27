/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:57:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/27 19:06:30 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_pipe_error(t_token *token_list)
{
	t_token	*aux;

	aux = token_list;
	if (aux->token[0][0] == '|')
		print_syntax_error(token_list, '|');
	while (aux)
	{
		if (aux->token[0][0] == '|'
			&& (aux->next == NULL || aux->next->token[0][0] == '|'))
			print_syntax_error(token_list, '|');
		aux = aux->next;
	}
}

static void	check_redirections_error(t_token *token_list)
{
	int		i;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			if (aux->token[i][0] == '<' || aux->token[i][0] == '>')
			{
				i++;
				if (aux->token[i] == NULL)
					print_syntax_error(token_list, '\n');
				else if (aux->token[i][0] == '<' || aux->token[i][0] == '>'
					|| aux->token[i][0] == '|')
					print_syntax_error(token_list, aux->token[i][0]);
			}
			i++;
		}
		aux = aux->next;
	}
}

static void	aux_check_quotes(t_token *token_list, char *a, int *j)
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
				print_syntax_error(token_list, '\n');
		}
		(*j)++;
	}
}

static void	check_quotes_error(t_token *token_list)
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
			aux_check_quotes(token_list, aux->token[i], &j);
			i++;
		}
		aux = aux->next;
	}
}

void	parser(t_token *token_list)
{
	check_pipe_error(token_list);
	check_redirections_error(token_list);
	check_quotes_error(token_list);
	expand_variable(token_list);
	remove_quotes(token_list);
	redirect_in_out(token_list);
}
