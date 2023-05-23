/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:28:40 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/22 22:17:32 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_token(char **token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i])
	{
		if (token[i][0] == '>' || token[i][0] == '<')
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

void	redirect_output(t_token *token_list)
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
					aux->fd[1] = open(aux->token[i + 1],
							O_RDWR | O_CREAT | O_TRUNC, 0644);
				else
					aux->fd[1] = open(aux->token[i + 1],
							O_RDWR | O_CREAT | O_APPEND, 0644);
				if (aux->redirect == 1)
					aux->redirect = REDIRECT_OUTPUT;
				else if (aux->redirect == REDIRECT_INPUT)
					aux->redirect = REDIRECT_BOTH;
			}
			i++;
		}
		update_token(aux->token);
		aux = aux->next;
	}
}

void	redirect_input(t_token *token_list)
{
	int		i;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			if (aux->token[i][0] == '<')
			{
				if (!aux->token[i][1])
				{
					aux->fd[0] = open(aux->token[i + 1], O_RDONLY);
				}
				else
					//heredoc
				if (aux->redirect == 1)
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
