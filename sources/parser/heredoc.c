/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:14:37 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/30 22:14:43 by lucade-s         ###   ########.fr       */
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

void	heredoc(t_token *token, int i)
{
	int		fd_heredoc;
	char	*prompt;

	fd_heredoc = open(".h*e*r*e*d*o*c*", O_RDWR | O_CREAT | O_TRUNC, 0644);
	prompt = NULL;
	while (1)
	{
		prompt = readline("> ");
		if (!ft_strncmp(prompt, token->token[i + 1],
				ft_strlen(token->token[i + 1]) + 1))
			break ;
		try_find_dollar_heredoc(&prompt);
		write(fd_heredoc, prompt, ft_strlen(prompt));
		write(fd_heredoc, "\n", 1);
		free(prompt);
	}
	free(prompt);
	close(fd_heredoc);
}
