/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:14:37 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/05 16:30:37 by lucade-s         ###   ########.fr       */
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

static void	heredoc_readline(char *dlmt)
{
	int		quotes;
	char	*prompt;

	quotes = 0;
	prompt = NULL;
	g_ms.on_fork = 2;
	signal(SIGINT, signal_handler_heredoc);
	while (1)
	{
		if (ft_strchr(dlmt, '\"') || ft_strchr(dlmt, '\''))
			remove_quotes_heredoc(dlmt, &quotes);
		prompt = readline("> ");
		if (!prompt || !ft_strncmp(prompt, dlmt, ft_strlen(dlmt) + 1))
		{
			print_error_heredoc(prompt, dlmt);
			break ;
		}
		if (!quotes)
			try_find_dollar_heredoc(&prompt);
		ft_putendl_fd(prompt, g_ms.fd_heredoc);
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
