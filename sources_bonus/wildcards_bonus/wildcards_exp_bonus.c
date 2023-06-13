/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_exp_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:00:23 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 17:34:47 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_list	*get_wildcards_expansion(char *token_i, char *path_prev)
{
	int				j;
	int				end_w_slash;
	char			*path;
	char			*aux_token;
	char			*aux_token2;
	t_list			*files;
	t_list			*aux_files;
	t_list			*cp_files;
	t_list			*aux_cp;
	t_list			*sub_files;
	DIR				*dir;
	struct dirent	*entry;

	j = 0;
	if (g_ms.first_wildcard)
	{
		path = ft_strdup(path_prev);
		g_ms.first_wildcard = 0;
	}
	else
	{
		aux_token = ft_strdup(token_i);
		if (ft_strchr(aux_token, '/'))
			*(ft_strchr(aux_token, '/') + 1) = '\0';
		path = ft_strjoin(path_prev, aux_token);
		free(aux_token);
		while (token_i[j] != '/')
			j++;
		while (token_i[j] == '/')
			j++;
	}
	aux_token = ft_strdup(token_i + j);
	files = NULL;
	dir = opendir(path);
	if (dir == NULL)
	{
		free(path);
		free(aux_token);
		return (NULL);
	}
	entry = readdir(dir);
	while (entry)
	{
		ft_lstadd_back(&files, ft_lstnew(ft_strdup(entry->d_name)));
		entry = readdir(dir);
	}
	closedir(dir);
	aux_token2 = ft_strdup(aux_token);
	end_w_slash = 0;
	if (ft_strchr(aux_token2, '/'))
	{
		*(ft_strchr(aux_token2, '/')) = '\0';
		end_w_slash = end_with_slash(aux_token2 + ft_strlen(aux_token2) + 1);
	}
	aux_get_wildcards(aux_token2, files);
	if (check_empty_subfiles(files))
	{
		free(path);
		free(aux_token);
		free(aux_token2);
		free_list(&files);
		return (NULL);
	}
	if (end_w_slash)
	{
		put_slash_dir(&files);
		free(path);
		free(aux_token);
		free(aux_token2);
		return (files);
	}
	cp_files = copy_list(files);
	if (ft_strchr(aux_token, '/'))
	{
		aux_cp = cp_files;
		while (aux_cp)
		{
			if (((char *)aux_cp->content)[0])
			{
				free(aux_token2);
				aux_token2 = ft_strjoin((char *)aux_cp->content, ft_strchr(aux_token, '/'));
				j = 0;
				sub_files = get_wildcards_expansion(aux_token2, path);
				cat_files(&files, sub_files);
				free_list(&sub_files);
			}
			aux_files = files->next;
			free(files->content);
			free(files);
			files = aux_files;
			aux_cp = aux_cp->next;
		}
	}
	else
	{
		free(path);
		free(aux_token);
		free(aux_token2);
		free_list(&cp_files);
		return (files);
	}
	free(path);
	free(aux_token);
	free(aux_token2);
	free_list(&cp_files);
	return (files);
}
