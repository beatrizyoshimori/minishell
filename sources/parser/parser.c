/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:57:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/31 19:24:46 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	aux_check_redirects(t_token *token, int i)
{
	if (token->token[i] == NULL)
	{
		if (token->next == NULL)
			print_syntax_error("newline");
		else
			print_syntax_error("|");
	}
	else if (token->token[i][0] == '<')
	{
		if (token->token[i][1] == '<')
			print_syntax_error("<<");
		else if (!token->token[i][1])
			print_syntax_error("<");
	}
	else if (token->token[i][0] == '>')
	{
		if (token->token[i][1] == '>')
			print_syntax_error(">>");
		else if (!token->token[i][1])
			print_syntax_error(">");
	}
}

static void	check_redirects_error(t_token *token_list)
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
				aux_check_redirects(aux, i);
				if (g_ms.syntax_error)
					return ;
			}
			i++;
		}
		aux = aux->next;
	}
}

static void	aux_check_quotes(char *aux, int *j)
{
	char	c;

	while (aux[*j])
	{
		c = aux[*j];
		if (c == '\'' || c == '\"')
		{
			(*j)++;
			while (aux[*j] && aux[*j] != c)
				(*j)++;
			if (aux[*j] == '\0')
			{
				print_syntax_error("newline");
				return ;
			}
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
			aux_check_quotes(aux->token[i], &j);
			if (g_ms.syntax_error)
				return ;
			i++;
		}
		aux = aux->next;
	}
}

void	parser(t_token *token_list)
{
	check_pipe_error(token_list);
	if (!g_ms.syntax_error)
		check_redirects_error(token_list);
	if (!g_ms.syntax_error)
		check_quotes_error(token_list);
	if (!g_ms.syntax_error)
	{
		expand_variable(token_list);
		redirect_heredoc(token_list);
		remove_quotes(token_list);
		redirect_in_out(token_list);
	}
}
