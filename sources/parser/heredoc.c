/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:14:37 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/31 22:24:51 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	try_find_dollar_heredoc(char **prompt)
{
	int	j;

	j = 0;
	while ((*prompt)[j])
	{
		if ((*prompt)[j] == '$')
		{
			if ((*prompt)[j + 1])
				j++;
			if ((*prompt)[j] == '?')
				put_exit_status(prompt, &j);
			else
				try_find_variable(prompt, &j);
		}
		if (*prompt)
			j++;
	}
}

static void	remove_quotes_heredoc(char *token_i, int *quotes)
{
	int	j;

	j = 0;
	while (token_i[j])
	{
		if (token_i[j] == '\'' || token_i[j] == '\"')
		{
			mark_quotes(&token_i, &j);
			*quotes = 1;
		}
		j++;
	}
	remove_quotes_aux(&token_i);
}

void	heredoc(t_token *token, int i)
{
	int		fd_heredoc;
	int		quotes;
	char	*prompt;

	quotes = 0;
	fd_heredoc = open(".h*e*r*e*d*o*c*", O_RDWR | O_CREAT | O_TRUNC, 0644);
	prompt = NULL;
	while (1)
	{
		if (ft_strchr(token->token[i + 1], '\"')
			|| ft_strchr(token->token[i + 1], '\''))
			remove_quotes_heredoc(token->token[i + 1], &quotes);
		prompt = readline("> ");
		if (!ft_strncmp(prompt, token->token[i + 1],
				ft_strlen(token->token[i + 1]) + 1))
			break ;
		if (!quotes)
			try_find_dollar_heredoc(&prompt);
		write(fd_heredoc, prompt, ft_strlen(prompt));
		write(fd_heredoc, "\n", 1);
		free(prompt);
	}
	free(prompt);
	close(fd_heredoc);
}

void	redirect_heredoc(t_token *token_list)
{
	int		i;
	int		ver;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		ver = 0;
		i = 0;
		while (aux->token[i] && !ver)
		{
			if (aux->token[i][0] == '<'
				&& aux->token[i][1] == '<' && !aux->token[i][2])
				heredoc(aux, i);
			i++;
		}
		aux = aux->next;
	}
}
