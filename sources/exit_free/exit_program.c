/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:04:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/08 20:49:11 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	check_quotes(char *prompt, char **aux)
// {
// 	int		i;
// 	int		length;
// 	char	c;

// 	i = 0;
// 	length = ft_strlen(prompt);
// 	if (prompt[0] == '\'' || prompt[0] == '\"')
// 		c = prompt[0];
// 	while (prompt[i] && prompt[i] == c)
// 		i++;
// 	length--;
// 	while (prompt[length] == c)
// 	{
// 		length--;
// 		i--;
// 	}
// 	if (i == 0 && prompt[length] == 't')
// 	{
// 		free(*aux);
// 		*aux = ft_strtrim(prompt, &c);
// 	}
// 	else if (i == 0 && (prompt[length] == '\'' || prompt[length] == '\"'))
// }

// void	exit_command(char *prompt, t_ms *ms)
// {
// 	char	*aux;

// 	aux = ft_strdup(prompt);
// 	check_quotes(prompt, &aux);
// 	if (!ft_strncmp(aux, "exit", 5))
// 	{
// 		rl_clear_history();
// 		free_split(ms->paths);
// 		free(ms);
// 		free(aux);
// 		free(prompt);
// 		exit(0);
// 	}
// 	else
// 		free(aux);
// }
void	exit_program(t_token **token_list, t_ms *ms)
{
	rl_clear_history();
	free_split(ms->paths);
	free(ms);
	free_token_list(token_list);
	exit(1);
}
