/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:20:17 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/12 22:05:26 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_when_exists(char **env, char *token_i, int length)
{
	int	j;

	j = 0;
	while (env[j])
	{	
		if ((!ft_strncmp(env[j], token_i, length) && env[j][length] == '='))
			return (1);
		if (!ft_strncmp(env[j], token_i, length)
			|| (!ft_strncmp(env[j], token_i, length - 1)
				&& !env[j][length - 1]))
		{
			free(env[j]);
			env[j] = ft_strdup(token_i);
			return (1);
		}
		j++;
	}
	return (0);
}

int	check_if_exists(t_token *token_list, int i)
{
	int	length;

	length = ft_strlen(token_list->token[i]);
	if (ft_strchr(token_list->token[i], '='))
		length = ft_strchr(token_list->token[i], '=')
			- &token_list->token[i][0] + 1;
	return (update_when_exists(token_list->ms->env,
			token_list->token[i], length));
}

int	check_isname(char *env_i)
{
	int	j;

	j = 0;
	if (env_i[j] != '_' && !ft_isalpha(env_i[j]))
		return (0);
	j++;
	while ((env_i[j] == '_' || ft_isalnum(env_i[j])) && env_i[j] != '=')
		j++;
	if (!env_i[j] || env_i[j] == '=')
		return (1);
	return (0);
}

static void	print_quotes(t_token *token_list, int i, int j)
{
	if (token_list->ms->env[i][j] == '=')
	{
		ft_putstr_fd("=\"", 1);
		j++;
		while (token_list->ms->env[i][j])
		{
			ft_putchar_fd(token_list->ms->env[i][j], 1);
			j++;
		}
		ft_putchar_fd('\"', 1);
	}
}

void	check_only_export(t_token *token_list)
{
	int	i;
	int	j;

	if (!token_list->token[1])
	{
		i = 0;
		while (token_list->ms->env[i])
		{
			ft_putstr_fd("declare -x ", 1);
			j = 0;
			while (token_list->ms->env[i][j]
				&& token_list->ms->env[i][j] != '=')
			{
				ft_putchar_fd(token_list->ms->env[i][j], 1);
				j++;
			}
			print_quotes(token_list, i, j);
			ft_putchar_fd('\n', 1);
			i++;
		}
		return ;
	}
}
