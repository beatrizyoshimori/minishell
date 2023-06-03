/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:14:37 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/03 20:04:29 by byoshimo         ###   ########.fr       */
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

static void	heredoc_readline(char *delimeter)
{
	int		quotes;
	char	*prompt;

	quotes = 0;
	prompt = NULL;
	g_ms.on_fork = 2;
	signal(SIGINT, signal_handler_heredoc);
	while (1)
	{
		if (ft_strchr(delimeter, '\"')
			|| ft_strchr(delimeter, '\''))
			remove_quotes_heredoc(delimeter, &quotes);
		prompt = readline("> ");
		if (!ft_strncmp(prompt, delimeter,
				ft_strlen(delimeter) + 1))
			break ;
		if (!quotes)
			try_find_dollar_heredoc(&prompt);
		write(g_ms.fd_heredoc, prompt, ft_strlen(prompt));
		write(g_ms.fd_heredoc, "\n", 1);
		free(prompt);
	}
	free(prompt);
	close(g_ms.fd_heredoc);
	exit_process(g_ms.token_list);
}

void	heredoc(t_token *token, int i)
{
	int		status;
	pid_t	pid;

	if (g_ms.exit_status == 148)
	{
		token->no_exec = 1;
		return ;
	}
	if (g_ms.fd_heredoc)
		close(g_ms.fd_heredoc);
	g_ms.fd_heredoc = open(".h*e*r*e*d*o*c*", O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (!pid)
		heredoc_readline(token->token[i + 1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_ms.exit_status = WEXITSTATUS(status);
	if (g_ms.exit_status == 148)
	{
		close(g_ms.fd_heredoc);
		g_ms.syntax_error = 1;
	}
	else
		g_ms.on_fork = 0;
}

void	redirect_heredoc(t_token *token_list)
{
	int		i;
	int		ver;
	t_token	*aux;

	aux = token_list;
	g_ms.token_list = token_list;
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
