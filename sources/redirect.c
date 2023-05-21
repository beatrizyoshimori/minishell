/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:28:40 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/20 20:58:47 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_token(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i][0] == '>')
		{
			free(token[i]);
			free(token[i + 1]);
			token[i] = NULL;
			token[i + 1] = NULL;
			if (token[i + 2])
			{
				token[i] = ft_strdup(token[i + 2]);
				if (token[i + 3])
					token[i + 1] = ft_strdup(token[i + 3]);
			}
			i++;
		}
		i++;
	}
}

void	redirect_output(t_token *token_list)
{
	int		i;
	int		fd;
	int		fd_backup;
	t_token	*aux;

	fd_backup = dup(1);
	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			if (aux->token[i][0] == '>' && !aux->token[i][1])
			{
				fd = open(aux->token[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
			}
			else if (aux->token[i][0] == '>' && aux->token[i][1] == '>')
			{
				fd = open(aux->token[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
			}
			i++;
		}
		update_token(aux->token);
		dup2(fd, 1);
		close(fd);
		aux = aux->next;
	}
	dup2(fd_backup, 1);
	close(fd_backup);
}

void	redirect_input(t_token *token_list)
{
	int		i;
	int		fd;
	int		fd_backup;
	t_token	*aux;

	fd_backup = dup(0);
	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			if (aux->token[i][0] == '<' && !aux->token[i][1])
			{
				fd = open(aux->token[i + 1], O_RDONLY);
			}
			else if (aux->token[i][0] == '<' && aux->token[i][1] == '<')
			{
				//heredoc
			}
			i++;
		}
		update_token(aux->token);
		dup2(fd, 1);
		close(fd);
		aux = aux->next;
	}
	dup2(fd_backup, 1);
	close(fd_backup);
}
