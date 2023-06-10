/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:38:06 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/09 20:58:39 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ft_strchr_wc(const char *s)
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

static void	free_list(t_list **files, char c)
{
	t_list	*aux;

	while (*files)
	{
		aux = (*files)->next;
		if (c == 'f')
			free((*files)->content);
		free(*files);
		*files = aux;
	}
}

static t_list	*copy_files(t_list *files)
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

static void	aux_expand_wildcards(char **token_i, t_list *files)
{
	int		j;
	int		k;
	int		length;
	char	*c;
	char	*aux;
	char	**split_wc;
	t_list	*cp_files;
	t_list	*aux_files;

	cp_files = copy_files(files);
	length = ft_strlen(*token_i);
	split_wc = ft_split(*token_i, WILDCARDS);
	if (!split_wc)
	{
		split_wc = (char **)ft_calloc(2, sizeof(char *));
		split_wc[0] = (char *)ft_calloc(1, sizeof(char));
	}
	aux_files = cp_files;
	while (aux_files)
	{
		j = 0;
		k = 0;
		while (split_wc[j])
		{
			if (j == 0 && (*token_i)[0] != WILDCARDS)
			{
				if (ft_strncmp((char *)aux_files->content, split_wc[j], ft_strlen(split_wc[j])))
				{
					((char *)aux_files->content)[0] = '\0';
					break ;
				}
				k += ft_strlen(split_wc[j]);
			}
			else if (!split_wc[j + 1])
			{
				if (ft_strlen(split_wc[j]) > ft_strlen((char *)aux_files->content + k) || ft_strncmp((char *)aux_files->content + ft_strlen((char *)aux_files->content) - ft_strlen(split_wc[j]), split_wc[j], ft_strlen(split_wc[j])))
				{
					((char *)aux_files->content)[0] = '\0';
					break ;
				}
			}
			else
			{
				c = ft_strnstr((char *)aux_files->content + k, split_wc[j], ft_strlen((char *)aux_files->content));
				if (!c)
				{
					((char *)aux_files->content)[0] = '\0';
					break ;
				}
				k = (c - (char *)aux_files->content) + ft_strlen(split_wc[j]);
			}
			j++;
		}
		aux_files = aux_files->next;
	}
	aux = (char *)ft_calloc(1, sizeof(char));
	aux_files = cp_files;
	while (aux_files)
	{
		if (((char *)aux_files->content)[0] != '.' && ((char *)aux_files->content)[0])
		{
			free(*token_i);
			*token_i = ft_strjoin(aux, (char *)aux_files->content);
			free(aux);
			aux = ft_strdup(*token_i);
			free(*token_i);
			if (aux_files->next)
				*token_i = ft_strjoin(aux, " ");
			free(aux);
			aux = ft_strdup(*token_i);
		}
		aux_files = aux_files->next;
	}
	j = 0;
	while ((*token_i)[j])
	{
		if ((*token_i)[j] == WILDCARDS)
			(*token_i)[j] = '*';
		j++;
	}
	free(aux);
	free_list(&cp_files, 'f');
	free_ptrptr(split_wc);
}

static void	expand_wildcards(char **token_i)
{
	int				j;
	char			*aux_token;
	char			*aux_token_search;
	char			*path;
	char			**split_aux;
	t_list			*files;
	DIR				*dir;
	struct dirent	*entry;

	j = 0;
	if ((*token_i)[0] == '/')
		path = ft_strdup("/");
	else if (!ft_strncmp((*token_i), "../", 3))
	{
		path = ft_strdup("..");
		j += 2;
	}
	else
	{
		path = getcwd(NULL, 0);
		if ((*token_i)[0] == '.')
			j++;
	}
	while ((*token_i)[j] == '/')
		j++;
	aux_token = ft_strdup(*token_i + j);
	files = NULL;
	dir = opendir(path);
	entry = readdir(dir);
	while (entry)
	{
		ft_lstadd_back(&files, ft_lstnew(entry->d_name));
		entry = readdir(dir);
	}
	aux_token_search = ft_strdup(aux_token);
	if (ft_strchr(aux_token_search, '/'))
		*(ft_strchr(aux_token_search, '/')) = '\0';
	aux_expand_wildcards(&aux_token_search, files);
	split_aux = ft_split(aux_token_search, ' ');
	if (ft_strchr(aux_token, '/'))
	{
		j = 0;
		while (split_aux[j])
		{
			free(aux_token_search);
			aux_token_search = ft_strjoin(split_aux[j], ft_strchr(aux_token, '/'));
			expand_wildcards(&aux_token_search);
			j++;
		}
	}
	else
	{
		free_ptrptr(split_aux);
		free_list(&files, 'n');
		closedir(dir);
		free(path);
		free(*token_i);
		*token_i = ft_strdup(aux_token_search);
		free(aux_token_search);
		free(aux_token);
		return ;
	}
	free_ptrptr(split_aux);
	free_list(&files, 'n');
	closedir(dir);
	free(path);
	free(aux_token_search);
	free(aux_token);
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
			if ((i == 0 || (i > 0 && ft_strncmp(aux->token[i - 1], "<<", 3)))
				&& ft_strchr_wc(aux->token[i]))
				expand_wildcards(&aux->token[i]);
			i++;
		}
		aux = aux->next;
	}
}
