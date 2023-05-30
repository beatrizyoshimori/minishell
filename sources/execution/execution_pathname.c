/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pathname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 22:02:24 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/29 22:02:41 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_pathname(t_token *token)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_ms.paths[i])
	{
		tmp = ft_strjoin(g_ms.paths[i], "/");
		token->pathname = ft_strjoin(tmp, token->token[0]);
		if (tmp)
			free(tmp);
		if (access(token->pathname, F_OK) == 0)
			return ;
		if (token->pathname)
			free(token->pathname);
		i++;
	}
	token->pathname = NULL;
}

void	set_pathname(t_token *token)
{
	if (token->token[0][0] == '/' && access(token->token[0], F_OK) == 0)
		token->pathname = ft_strdup(token->token[0]);
	else if (ft_isfile(token->token[0])
		&& access(token->token[0], F_OK | X_OK) == -1)
	{
		print_error("bilu: ", token->token[0], strerror(errno));
		token->no_exec = 1;
		g_ms.printed_error = 1;
		if (access(token->token[0], F_OK) == -1)
			g_ms.exit_status = 127;
		else
			g_ms.exit_status = 126;
	}
	else
		find_pathname(token);
}
