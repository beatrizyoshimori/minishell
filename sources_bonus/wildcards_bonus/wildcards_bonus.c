/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:38:06 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 22:32:35 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	recursion_wildcards(t_list **files, char *aux_token, char *path)
{
	char	*aux;
	t_list	*cp_files;
	t_list	*aux_cp;
	t_list	*sub_files;

	cp_files = copy_list(*files);
	if (ft_strchr(aux_token, '/'))
	{
		aux_cp = cp_files;
		while (aux_cp)
		{
			if (((char *)aux_cp->content)[0])
			{
				aux = ft_strjoin((char *)aux_cp->content,
						ft_strchr(aux_token, '/'));
				sub_files = get_wildcards_expansion(aux, path);
				free(aux);
				cat_files(files, sub_files);
				free_list(&sub_files);
			}
			delete_node_list(files);
			aux_cp = aux_cp->next;
		}
	}
	free_all_wc(cp_files, path, aux_token, NULL);
}

t_list	*get_wildcards_expansion(char *token_i, char *path_prev)
{
	int				end_w_slash;
	char			*path;
	char			*aux_token;
	char			*aux_token2;
	t_list			*files;

	aux_token = NULL;
	files = NULL;
	path = get_path_wc(token_i, path_prev, &aux_token);
	if (!get_files(&files, path, aux_token))
		return (NULL);
	aux_token2 = ft_strdup(aux_token);
	end_w_slash = end_with_slash(aux_token2);
	aux_get_wildcards(aux_token2, files);
	if (check_empty_subfiles(files, path, aux_token, aux_token2))
		return (NULL);
	if (end_w_slash)
	{
		free_all_wc(NULL, path, aux_token, aux_token2);
		return (files);
	}
	recursion_wildcards(&files, aux_token, path);
	free(aux_token2);
	return (files);
}

static void	expand_wildcards(t_token *token, int i)
{
	int		j;
	char	*first_path;
	t_list	*wildcards;

	if (ft_strchr_wc(token->token[i])
		&& (i == 0 || (i > 0 && ft_strncmp(token->token[i - 1], "<<", 3))))
	{
		g_ms.first_wildcard = 1;
		j = get_first_path(token->token[i], &first_path);
		wildcards = get_wildcards_expansion(token->token[i] + j, first_path);
		if (j == 0)
		{
			free(first_path);
			first_path = NULL;
		}
		if (wildcards)
			put_wildcards(token, &i, first_path, wildcards);
		else
			change_back_asterisc(&token->token[i]);
		free(first_path);
	}
}

void	wildcards(t_token *token_list)
{
	int		i;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			expand_wildcards(aux, i);
			i++;
		}
		aux = aux->next;
	}
}
