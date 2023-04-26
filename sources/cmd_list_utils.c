/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:39:12 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/25 19:39:29 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_last(t_cmd *cmd)
{
	if (cmd == NULL)
		return (cmd);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	ft_cmd_last(*cmd)->next = new;
}
