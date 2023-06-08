/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:38:06 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/07 20:59:38 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	free_list(t_list **files)
{
	t_list	*aux;

	while (*files)
	{
		aux = (*files)->next;
		free(*files);
		*files = aux;
	}
}

static void	expand_wildcards(char **aux_token_i, t_list *files)
{
	char	*aux;
	char	**split_wc;
	t_list	*aux_files;

	split_wc = ft_split(*aux_token_i, WILDCARDS);
	if (!(*split_wc))
	{
		aux = (char *)ft_calloc(1, sizeof(char));
		aux_files = files;
		while (aux_files)
		{
			if (((char *)aux_files->content)[0] != '.')
			{
				free(*aux_token_i);
				*aux_token_i = ft_strjoin(aux, (char *)aux_files->content);
				free(aux);
				aux = ft_strdup(*aux_token_i);
				free(*aux_token_i);
				*aux_token_i = ft_strjoin(aux, " ");
				free(aux);
				aux = ft_strdup(*aux_token_i);
			}
			aux_files = aux_files->next;
		}
		free(aux);
	}
	free_ptrptr(split_wc);
}

void	try_find_wildcards(t_token *token_list, t_list *files)
{
	int		i;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			if (i == 0 || (i > 0 && ft_strncmp(aux->token[i - 1], "<<", 3)))
				expand_wildcards(&aux->token[i], files);
			i++;
		}
		aux = aux->next;
	}
}

void	wildcards(t_token *token_list)
{
	char			*pwd;
	t_list			*files;
	DIR				*dir;
	struct dirent	*entry;

	files = NULL;
	pwd = getcwd(NULL, 0);
	dir = opendir(pwd);
	entry = readdir(dir);
	while (entry)
	{
		ft_lstadd_back(&files, ft_lstnew(entry->d_name));
		entry = readdir(dir);
	}
	try_find_wildcards(token_list, files);
	free_list(&files);
	closedir(dir);
	free(pwd);
}
