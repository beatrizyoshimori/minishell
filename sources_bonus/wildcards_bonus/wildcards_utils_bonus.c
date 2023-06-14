/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:13:30 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 21:32:11 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_strchr_wc(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == WILDCARDS)
			return (1);
		i++;
	}
	return (0);
}

int	end_with_slash(char *token_i)
{
	int		j;
	char	*aux;

	if (ft_strchr(token_i, '/'))
	{
		*(ft_strchr(token_i, '/')) = '\0';
		aux = ft_strdup(token_i + ft_strlen(token_i) + 1);
		j = 0;
		while (aux[j] == '/')
			j++;
		if (!aux[j])
		{
			free(aux);
			return (1);
		}
		free(aux);
	}
	return (0);
}

int	get_first_path(char *token_i, char **first_path)
{
	int		j;

	j = 0;
	while (token_i[j] == '.' || token_i[j] == '/')
		j++;
	*first_path = ft_strdup(token_i);
	(*first_path)[j] = '\0';
	if (!ft_strchr(*first_path, '/'))
	{
		free(*first_path);
		*first_path = ft_strdup("./");
		return (0);
	}
	*(ft_strrchr(*first_path, '/') + 1) = '\0';
	return (ft_strlen(*first_path));
}

char	**copy_ptrptr(char **ptrptr)
{
	int		i;
	char	**cp_ptrptr;

	i = 0;
	while (ptrptr[i])
		i++;
	cp_ptrptr = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (ptrptr[i])
	{
		cp_ptrptr[i] = ft_strdup(ptrptr[i]);
		i++;
	}
	return (cp_ptrptr);
}

void	change_back_asterisc(char **token_i)
{
	int	j;

	j = 0;
	while ((*token_i)[j])
	{
		if ((*token_i)[j] == WILDCARDS)
			(*token_i)[j] = '*';
		j++;
	}
}
