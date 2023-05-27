/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:28:40 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/27 19:57:47 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_token *token, int i)
{
	int		fd_heredoc;
	char	*prompt;

	fd_heredoc = open(".h*e*r*e*d*o*c*", O_RDWR | O_CREAT | O_TRUNC, 0644);
	prompt = NULL;
	while (1)
	{
		prompt = readline("> ");
		if (!ft_strncmp(prompt, token->token[i + 1], ft_strlen(token->token[i + 1]) + 1))
			break ;
		write(fd_heredoc, prompt, ft_strlen(prompt));
		write(fd_heredoc, "\n", 1);
		free(prompt);
	}
	free(prompt);
	close(fd_heredoc);
}

static void	update_token(char **token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i])
	{
		if ((token[i][0] == '>' && (token[i][1] == '>' || !token[i][1]))
			|| (token[i][0] == '<' && (token[i][1] == '<' || !token[i][1])))
		{
			free(token[i]);
			free(token[i + 1]);
			token[i] = NULL;
			token[i + 1] = NULL;
			j = i + 2;
			while (token[j])
			{
				token[j - 2] = ft_strdup(token[j]);
				free(token[j]);
				token[j] = NULL;
				j++;
			}
			i--;
		}
		i++;
	}
}

void	redirect_in_out(t_token *token_list)
{
	int		i;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			if (aux->token[i][0] == '>')
			{
				if (!aux->token[i][1])
				{
					aux->fd[1] = open(aux->token[i + 1],
							O_RDWR | O_CREAT | O_TRUNC, 0644);
					if (aux->fd[1] == -1)
					{
						if (!g_ms.print_error)
						{
							ft_putstr_fd("bilu: ", 2);
							ft_putstr_fd(aux->token[i + 1], 2);
							ft_putstr_fd(": ", 2);
							ft_putstr_fd(strerror(errno), 2);
							ft_putstr_fd("\n", 2);
						}
						g_ms.exit_status = 1;
						g_ms.print_error = 1;
						aux->exec = 1;
						break ;
					}
				}
				else if (aux->token[i][1] == '>')
				{
					aux->fd[1] = open(aux->token[i + 1],
							O_RDWR | O_CREAT | O_APPEND, 0644);
					if (aux->fd[1] == -1)
					{
						if (!g_ms.print_error)
						{
							ft_putstr_fd("bilu: ", 2);
							ft_putstr_fd(aux->token[i + 1], 2);
							ft_putstr_fd(": ", 2);
							ft_putstr_fd(strerror(errno), 2);
							ft_putstr_fd("\n", 2);
						}
						g_ms.exit_status = 1;
						g_ms.print_error = 1;
						aux->exec = 1;
						break ;
					}
				}
				if (aux->redirect == NO_REDIRECT)
					aux->redirect = REDIRECT_OUTPUT;
				else if (aux->redirect == REDIRECT_INPUT)
					aux->redirect = REDIRECT_BOTH;
			}
			else if (aux->token[i][0] == '<')
			{
				if (!aux->token[i][1])
				{
					aux->fd[0] = open(aux->token[i + 1], O_RDONLY);
					if (aux->fd[0] == -1)
					{
						if (!g_ms.print_error)
						{
							ft_putstr_fd("bilu: ", 2);
							ft_putstr_fd(aux->token[i + 1], 2);
							ft_putstr_fd(": ", 2);
							ft_putstr_fd(strerror(errno), 2);
							ft_putstr_fd("\n", 2);
						}
						g_ms.exit_status = 1;
						g_ms.print_error = 1;
						aux->exec = 1;
						break ;
					}
				}
				else if (aux->token[i][1] == '<')
				{
					heredoc(aux, i);
					aux->fd[0] = open(".h*e*r*e*d*o*c*", O_RDONLY);
				}
				if (aux->redirect == NO_REDIRECT)
					aux->redirect = REDIRECT_INPUT;
				else if (aux->redirect == REDIRECT_OUTPUT)
					aux->redirect = REDIRECT_BOTH;
			}
			i++;
		}
		update_token(aux->token);
		aux = aux->next;
	}
}
