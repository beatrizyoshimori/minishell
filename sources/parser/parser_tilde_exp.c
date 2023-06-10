/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tilde_exp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:40:02 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/09 13:00:46 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_tilde(char **token_i, char *home, int *j)
{
	char	*aux;

	aux = (char *)ft_calloc(ft_strlen(*token_i)
			+ ft_strlen(home), sizeof(char));
	ft_strlcpy(aux, *token_i, *j + 1);
	ft_strlcpy(&aux[*j], home, ft_strlen(home) + 1);
	ft_strlcpy(&aux[*j + ft_strlen(home)],
		&(*token_i)[*j + 1], ft_strlen(*token_i) - *j);
	free(*token_i);
	*token_i = ft_strdup(aux);
	*j = *j + ft_strlen(home);
	free(aux);
}

static int	check_isname_tilde(char *token_i, int *j)
{
	int	i;

	if (token_i[0] != '_' && !ft_isalpha(token_i[0]))
		return (0);
	i = 1;
	while (i < *j - 1)
	{
		if (token_i[i] != '_' && !ft_isalnum(token_i[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	try_find_home(char **token_i, int *j)
{
	int		i;
	char	*home;

	if (*j != 0 && !check_isname_tilde(*token_i, j))
	{
		(*token_i)[*j] = '~';
		return ;
	}
	i = 0;
	while (g_ms.env[i])
	{
		if (!ft_strncmp(g_ms.env[i], "HOME=", 5))
		{
			home = ft_strdup(g_ms.env[i] + 5);
			break ;
		}
		i++;
	}
	if (!g_ms.env[i])
		home = ft_strdup(g_ms.home);
	expand_tilde(token_i, home, j);
	free(home);
}

void	try_find_tilde(char **token_i)
{
	int	j;

	j = 0;
	while ((*token_i)[j])
	{
		if ((*token_i)[j] == TILDE_VAR)
			try_find_home(token_i, &j);
		if ((*token_i)[j])
			j++;
	}
}
