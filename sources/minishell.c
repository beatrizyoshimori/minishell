/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:53 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/24 20:06:14 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_prompt(t_cmd **cmd)
{
	t_cmd	*tmp;
	char	*prompt;
	char	**line;

	tmp = *cmd;
	while (1)
	{
		prompt = readline("lúbia> ");
		printf("%s\n", prompt);
		line = ft_split(prompt, ' ');
	}
}

int main(void)
{
	t_cmd	*cmd;

	create_prompt(&cmd);
	return (0);
}