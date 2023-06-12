/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:38:06 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/12 19:07:39 by lucade-s         ###   ########.fr       */
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

static void	free_list(t_list **files)
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

static t_list	*copy_list(t_list *files)
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

static void	aux_expand_wildcards(char *token_i, t_list *files)
{
	int		j;
	int		k;
	int		length;
	char	*c;
	char	**split_wc;
	t_list	*aux_files;

	length = ft_strlen(token_i);
	split_wc = ft_split(token_i, WILDCARDS);
	if (!split_wc[0])
	{
		free(split_wc);
		split_wc = (char **)ft_calloc(2, sizeof(char *));
		split_wc[0] = (char *)ft_calloc(1, sizeof(char));
	}
	else
		g_ms.show_hidden_folders = 1;
	aux_files = files;
	while (aux_files)
	{
		j = 0;
		k = 0;
		while (split_wc[j])
		{
			if (j == 0 && token_i[0] != WILDCARDS)
			{
				if (ft_strncmp((char *)aux_files->content, split_wc[j], ft_strlen(split_wc[j])))
				{
					((char *)aux_files->content)[0] = '\0';
					break ;
				}
				k += ft_strlen(split_wc[j]);
			}
			else if (!split_wc[j + 1] && token_i[length - 1] != WILDCARDS)
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
	free_ptrptr(split_wc);
}

static void	cat_files(t_list **dir, t_list *sub_files)
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

static t_list	*expand_wildcards(char *token_i, char *path_prev)
{
	char			*path;
	int				j;
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
	if (ft_strchr(aux_token2, '/'))
		*(ft_strchr(aux_token2, '/')) = '\0';
	aux_expand_wildcards(aux_token2, files);
	cp_files = copy_list(files);
	if (ft_strchr(aux_token, '/'))
	{
		printf("aux_token: %s\n", aux_token);
		aux_cp = cp_files;
		while (aux_cp)
		{
			if (((char *)aux_cp->content)[0])
			{
				free(aux_token2);
				aux_token2 = ft_strjoin((char *)aux_cp->content, ft_strchr(aux_token, '/'));
				j = 0;
				sub_files = expand_wildcards(aux_token2, path);
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
		free(aux_token2);
		free(aux_token);
		free_list(&cp_files);
		return (files);
	}
	free(path);
	free(aux_token2);
	free(aux_token);
	free_list(&cp_files);
	return (files);
}

static char	**copy_ptrptr(char **ptrptr)
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

static void	put_wildcards(t_token *token, int *i, char *first_path, t_list *wildcards)
{
	int		aux_i;
	int		j;
	char	**cp_token;
	t_list	*aux_wildcards;
	
	j = 0;
	while (token->token[j])
		j++;
	j--;
	aux_wildcards = wildcards;
	while (aux_wildcards)
	{
		if (((((char *)aux_wildcards->content)[0] == '.' && g_ms.show_hidden_folders) || ((char *)aux_wildcards->content)[0] != '.') && ((char *)aux_wildcards->content)[0])
			j++;
		aux_wildcards = aux_wildcards->next;
	}
	aux_i = *i;
	*i = j - 1;
	cp_token = copy_ptrptr(token->token);
	free_ptrptr(token->token);
	token->token = (char **)ft_calloc(j + 1, sizeof(char *));
	j = 0;
	while (j < aux_i)
	{
		token->token[j] = ft_strdup(cp_token[j]);
		j++;
	}
	aux_i++;
	aux_wildcards = wildcards;
	while (aux_wildcards)
	{
		if (((((char *)aux_wildcards->content)[0] == '.' && g_ms.show_hidden_folders) || ((char *)aux_wildcards->content)[0] != '.') && ((char *)aux_wildcards->content)[0])
		{
			if (!first_path)
				token->token[j] = ft_strdup((char *)aux_wildcards->content);
			else
				token->token[j] = ft_strjoin(first_path, (char *)aux_wildcards->content);
			j++;
		}
		aux_wildcards = aux_wildcards->next;
	}
	while (cp_token[aux_i])
	{
		token->token[j] = ft_strdup(cp_token[aux_i]);
		aux_i++;
		j++;
	}
	free_ptrptr(cp_token);
}

static int	get_first_path(char *token_i, char **first_path)
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

static void	change_back_asterisc(char **token_i)
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

void	wildcards(t_token *token_list)
{
	int		i;
	int		j;
	char	*first_path;
	t_token	*aux;
	t_list	*wildcards;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			if (ft_strchr_wc(aux->token[i]) && (i == 0 || (i > 0 && ft_strncmp(aux->token[i - 1], "<<", 3))))
			{
				g_ms.first_wildcard = 1;
				j = get_first_path(aux->token[i], &first_path);
				wildcards = expand_wildcards(aux->token[i] + j, first_path);
				if (j == 0)
				{
					free(first_path);
					first_path = NULL;
				}
				if (wildcards)
				{
					put_wildcards(aux, &i, first_path, wildcards);
					free_list(&wildcards);
				}
				else
					change_back_asterisc(&aux->token[i]);
				free(first_path);
			}
			i++;
		}
		aux = aux->next;
	}
}
