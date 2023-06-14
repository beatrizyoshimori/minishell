/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_list_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:10:31 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 21:42:44 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	check_empty_subfiles(t_list *files, char *path,
	char *aux_token, char *aux_token2)
{
	t_list	*aux;

	aux = files;
	while (aux)
	{
		if (((char *)aux->content)[0])
			return (0);
		aux = aux->next;
	}
	free_all_wc(files, path, aux_token, aux_token2);
	return (1);
}

void	free_list(t_list **files)
{
	t_list	*aux;

	while (*files)
	{
		aux = (*files)->next;
		free((*files)->content);
		free(*files);
		*files = aux;
	}
}

void	cat_files(t_list **dir, t_list *sub_files)
{
	t_list	*aux_sub;
	char	*aux;

	aux_sub = sub_files;
	while (aux_sub)
	{
		if (((char *)aux_sub->content)[0])
		{
			aux = ft_strjoin("/", (char *)aux_sub->content);
			ft_lstadd_back(dir, ft_lstnew(ft_strjoin((*dir)->content, aux)));
			free(aux);
		}
		aux_sub = aux_sub->next;
	}
}

void	put_slash_dir(t_list **files)
{
	char		*aux;
	t_list		*cp_files;
	t_list		*aux_files;
	t_list		*aux_cp;
	struct stat	statbuf;

	statbuf = (struct stat){0};
	cp_files = copy_list(*files);
	aux_cp = cp_files;
	while (aux_cp)
	{
		stat((char *)aux_cp->content, &statbuf);
		if (((char *)aux_cp->content)[0] && S_ISDIR(statbuf.st_mode))
		{
			aux = ft_strdup((*files)->content);
			ft_lstadd_back(files, ft_lstnew(ft_strjoin(aux, "/")));
			free(aux);
		}
		aux_files = (*files)->next;
		free((*files)->content);
		free(*files);
		*files = aux_files;
		aux_cp = aux_cp->next;
	}
	free_list(&cp_files);
}

t_list	*copy_list(t_list *files)
{
	t_list	*aux;
	t_list	*cp_files;

	cp_files = NULL;
	aux = files;
	while (aux)
	{
		ft_lstadd_back(&cp_files, ft_lstnew(ft_strdup(aux->content)));
		aux = aux->next;
	}
	return (cp_files);
}
