/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_var_exp_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:06:35 by lucade-s          #+#    #+#             */
/*   Updated: 2023/05/14 18:08:35 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_length_after_dollar(char *token_i, int *j)
{
	int	length;

	length = 0;
	if (token_i[*j] == '_' || ft_isalpha(token_i[*j]))
	{
		while (token_i[*j] == '_' || ft_isalnum(token_i[*j]))
		{
			length++;
			(*j)++;
		}
	}
	else
	{
		while (token_i[*j] && token_i[*j] != '_' && !ft_isalpha(token_i[*j]))
		{
			length++;
			(*j)++;
		}
	}
	return (length);
}

void	found_variable(char **token_i, char *env_i, int **j, int *length)
{
	char	*aux;

	aux = (char *)ft_calloc(ft_strlen(*token_i)
			+ ft_strlen(env_i), sizeof(char));
	ft_strlcpy(aux, *token_i, **j - *length);
	ft_strlcpy(&aux[**j - *length - 1], &env_i[*length + 1],
		ft_strlen(env_i) - *length);
	ft_strlcpy(&aux[**j - 2 * *length + ft_strlen(env_i) - 2],
		&(*token_i)[**j], ft_strlen(*token_i) - **j + 1);
	free(*token_i);
	*token_i = ft_strdup(aux);
	**j = **j + ft_strlen(env_i) - 2 * (*length + 1) - 1;
	free(aux);
}

void	not_found_variable(char **token_i, int **j, int *length)
{
	char	*aux;

	aux = (char *)ft_calloc(ft_strlen(*token_i), sizeof(char));
	ft_strlcpy(aux, *token_i, **j - *length);
	ft_strlcpy(&aux[**j - *length - 1],
		&(*token_i)[**j], ft_strlen(*token_i) - **j + 1);
	free(*token_i);
	*token_i = ft_strdup(aux);
	**j = **j - *length - 2;
	free(aux);
}
