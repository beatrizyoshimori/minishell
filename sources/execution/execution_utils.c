/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 22:04:36 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/29 22:04:50 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdirectory(char *token_cmd)
{
	struct stat	statbuf;

	if (stat(token_cmd, &statbuf) != 0)
		return (0);
	if (S_ISDIR(statbuf.st_mode))
	{
		if (*token_cmd == '.')
			token_cmd++;
		if (*token_cmd == '.')
			token_cmd++;
		if (*token_cmd == '/')
			return (1);
	}
	return (0);
}

int	ft_isfile(char *token_cmd)
{
	if (*token_cmd == '.')
		token_cmd++;
	if (*token_cmd == '.')
		token_cmd++;
	if (*token_cmd == '/')
		return (1);
	return (0);
}
