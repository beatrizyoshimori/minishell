/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:28:40 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/31 22:23:44 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_fd_error(t_token *token, int i, int index, int *ver)
{
	if (token->fd[index] == -1)
	{
		print_error("bilu: ", token->token[i + 1], strerror(errno), 1);
		token->no_exec = 1;
		*ver = 1;
	}
}

static void	set_redirect_fd(t_token *token, int i, int red_open, int *ver)
{
	int	index;

	index = 1;
	if (red_open == RED_OUT_TRUNC)
	{
		if (token->fd[1])
			close(token->fd[1]);
		token->fd[1] = open(token->token[i + 1],
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else if (red_open == RED_OUT_APPEND)
	{
		if (token->fd[1])
			close(token->fd[1]);
		token->fd[1] = open(token->token[i + 1],
				O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		if (token->fd[0])
			close(token->fd[0]);
		token->fd[0] = open(token->token[i + 1], O_RDONLY);
		index = 0;
	}
	check_fd_error(token, i, index, ver);
}

static void	redirect_output(t_token *token, int i, int *ver)
{
	if (!token->token[i + 1])
	{
		print_error("bilu", "", "ambiguos redirect", 1);
		token->no_exec = 1;
		*ver = 1;
		return ;
	}
	if (!token->token[i][1])
		set_redirect_fd(token, i, RED_OUT_TRUNC, ver);
	else if (token->token[i][1] == '>' && !token->token[i][2])
		set_redirect_fd(token, i, RED_OUT_APPEND, ver);
	if (token->redirect == NO_REDIRECT)
		token->redirect = REDIRECT_OUTPUT;
	else if (token->redirect == REDIRECT_INPUT)
		token->redirect = REDIRECT_BOTH;
}

void	redirect_input(t_token *token, int i, int *ver)
{
	if (!token->token[i + 1])
	{
		print_error("bilu", "", "ambiguos redirect", 1);
		token->no_exec = 1;
		*ver = 1;
		return ;
	}
	if (!token->token[i][1])
		set_redirect_fd(token, i, RED_IN, ver);
	else if (token->token[i][1] == '<' && !token->token[i][2])
	{
		if (token->fd[0])
			close(token->fd[0]);
		token->fd[0] = open(".h*e*r*e*d*o*c*", O_RDONLY);
	}
	if (token->redirect == NO_REDIRECT)
		token->redirect = REDIRECT_INPUT;
	else if (token->redirect == REDIRECT_OUTPUT)
		token->redirect = REDIRECT_BOTH;
}

void	redirect_in_out(t_token *token_list)
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
			if (aux->token[i][0] == '>' && (!aux->token[i][1]
				|| (aux->token[i][1] == '>' && !aux->token[i][2])))
				redirect_output(aux, i, &ver);
			else if (aux->token[i][0] == '<' && (!aux->token[i][1]
				|| (aux->token[i][1] == '<' && !aux->token[i][2])))
				redirect_input(aux, i, &ver);
			i++;
		}
		update_token(aux->token);
		aux = aux->next;
	}
}
