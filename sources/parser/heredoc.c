/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:14:37 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/03 19:20:16 by byoshimo         ###   ########.fr       */
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

static void	signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_ms.exit_status = 148;
		close(g_ms.fd_heredoc);
		exit_process(g_ms.token_list);
	}
}

void	heredoc(t_token *token, int i)
{
	int		quotes;
	int		status;
	pid_t	pid;
	char	*prompt;

	g_ms.fd_heredoc = open(".h*e*r*e*d*o*c*", O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (!pid)
	{
		g_ms.on_fork = 2;
		quotes = 0;
		signal(SIGINT, signal_handler_heredoc);
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
			write(g_ms.fd_heredoc, prompt, ft_strlen(prompt));
			write(g_ms.fd_heredoc, "\n", 1);
			free(prompt);
		}
		free(prompt);
		close(g_ms.fd_heredoc);
		exit_process(g_ms.token_list);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_ms.exit_status = WEXITSTATUS(status);
	if (g_ms.exit_status == 148)
		g_ms.syntax_error = 1;
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
