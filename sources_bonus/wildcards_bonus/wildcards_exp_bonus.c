/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_exp_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:00:23 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 22:26:27 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*get_path_wc(char *token_i, char *path_prev, char **aux_token)
{
	int		j;
	char	*path;

	j = 0;
	if (g_ms.first_wildcard)
	{
		path = ft_strdup(path_prev);
		g_ms.first_wildcard = 0;
	}
	else
	{
		*aux_token = ft_strdup(token_i);
		if (ft_strchr(*aux_token, '/'))
			*(ft_strchr(*aux_token, '/') + 1) = '\0';
		path = ft_strjoin(path_prev, *aux_token);
		free(*aux_token);
		while (token_i[j] != '/')
			j++;
		while (token_i[j] == '/')
			j++;
	}
	*aux_token = ft_strdup(token_i + j);
	return (path);
}

int	get_files(t_list **files, char *path, char *aux_token)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (dir == NULL)
	{
		free(path);
		free(aux_token);
		return (0);
	}
	entry = readdir(dir);
	while (entry)
	{
		ft_lstadd_back(files, ft_lstnew(ft_strdup(entry->d_name)));
		entry = readdir(dir);
	}
	closedir(dir);
	return (1);
}

void	free_all_wc(t_list *files, char *path,
	char *aux_token, char *aux_token2)
{
	free(path);
	free(aux_token);
	free(aux_token2);
	free_list(&files);
}

void	delete_node_list(t_list **files)
{
	t_list	*aux_files;

	aux_files = (*files)->next;
	free((*files)->content);
	free(*files);
	*files = aux_files;
}
