/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:38:06 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/10 18:48:00 by lucade-s         ###   ########.fr       */
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
	if (!split_wc)
	{
		split_wc = (char **)ft_calloc(2, sizeof(char *));
		split_wc[0] = (char *)ft_calloc(1, sizeof(char));
	}
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

static void	cat_files(t_list **dir, t_list *sub_files, char *slash)
{
	t_list	*aux_sub;
	char	*aux;

	aux_sub = sub_files;
	while (aux_sub)
	{
		if (((char *)aux_sub->content)[0])
		{
			aux = ft_strjoin(slash, (char *)aux_sub->content);
			ft_lstadd_back(dir, ft_lstnew(ft_strjoin((*dir)->content, aux)));
			free(aux);
		}
		aux_sub = aux_sub->next;
	}
	aux_sub = (*dir)->next;
	free((*dir)->content);
	free(*dir);
	*dir = aux_sub;
}

static t_list	*expand_wildcards(char *token_i)
{
	static int		first = 1;
	static char		*path;
	int				j;
	char			*aux_token;
	char			*aux_token2;
	char			*slash;
	t_list			*files;
	t_list			*aux_files;
	t_list			*cp_files;
	t_list			*aux_cp;
	t_list			*sub_files;
	DIR				*dir;
	struct dirent	*entry;

	j = 0;
	if (token_i[0] == '/')
		path = ft_strdup("/");
	else if (!ft_strncmp(token_i, "../", 3))
	{
		path = ft_strdup("../");
		j += 2;
	}
	else
	{
		if (first)
			path = ft_strdup("./");
		else
		{
			aux_token = ft_strdup(token_i);
			if (ft_strchr(aux_token, '/'))
				*(ft_strchr(aux_token, '/') + 1) = '\0';
			printf("aux_token: %s\n", aux_token);
			aux_token2 = ft_strdup(path);
			free(path);
			path = ft_strjoin(aux_token2, aux_token);
			free(aux_token);
			free(aux_token2);
			while (token_i[j] != '/')
				j++;
		}
		if (token_i[0] == '.')
			j++;
	}
	first = 0;
	printf("path: %s\n", path);
	while (token_i[j] == '/')
		j++;
	aux_token = ft_strdup(token_i + j);
	files = NULL;
	dir = opendir(path);
	free(path);
	entry = readdir(dir);
	printf("OI\n");
	while (entry)
	{
		ft_lstadd_back(&files, ft_lstnew(ft_strdup(entry->d_name)));
		entry = readdir(dir);
	}
	closedir(dir);
	printf("files:\n");
	print_list_wc(files);
	aux_token2 = ft_strdup(aux_token);
	if (ft_strchr(aux_token2, '/'))
		*(ft_strchr(aux_token2, '/')) = '\0';
	aux_expand_wildcards(aux_token2, files);
	cp_files = copy_files(files);
	if (ft_strchr(aux_token, '/'))
	{
		aux_cp = cp_files;
		while (aux_cp)
		{
			if (((char *)aux_cp->content)[0])
			{
				free(aux_token2);
				aux_token2 = ft_strjoin((char *)aux_cp->content, ft_strchr(aux_token, '/'));
				slash = ft_strdup(ft_strchr(aux_token, '/'));
				j = 0;
				while (slash[j] == '/')
					j++;
				slash[j] = '\0';
				sub_files = expand_wildcards(aux_token2);
				printf("sub_files:\n");
				print_list_wc(sub_files);
				cat_files(&files, sub_files, slash);
				printf("files:\n");
				print_list_wc(files);
				free(slash);
				free_list(&sub_files);
			}
			else
			{
				aux_files = files->next;
				free(files->content);
				free(files);
				files = aux_files;
				// printf("files:\n");
				// print_list_wc(files);
			}
			aux_cp = aux_cp->next;
		}
	}
	else
	{
		free(aux_token2);
		free(aux_token);
		free_list(&cp_files);
		return (files);
	}
	free(aux_token2);
	free(aux_token);
	free_list(&cp_files);
	return (files);
}

// static void	put_wildcards(char **token_i, t_list *wildcards)
// {
// 	int		j;
// 	char	*aux;
// 	t_list	*aux_wildcards;
	
// 	aux = (char *)ft_calloc(1, sizeof(char));
// 	aux_wildcards = wildcards;
// 	while (aux_wildcards)
// 	{
// 		if (((char *)aux_wildcards->content)[0] != '.' && ((char *)aux_wildcards->content)[0])
// 		{
// 			free(*token_i);
// 			*token_i = ft_strjoin(aux, (char *)aux_wildcards->content);
// 			free(aux);
// 			aux = ft_strdup(*token_i);
// 			free(*token_i);
// 			if (aux_wildcards->next)
// 				*token_i = ft_strjoin(aux, " ");
// 			else
// 				*token_i = ft_strdup(aux);
// 			free(aux);
// 			aux = ft_strdup(*token_i);
// 		}
// 		aux_wildcards = aux_wildcards->next;
// 	}
// 	j = 0;
// 	while ((*token_i)[j])
// 	{
// 		if ((*token_i)[j] == WILDCARDS)
// 			(*token_i)[j] = '*';
// 		j++;
// 	}
// 	free(aux);
// }

void	wildcards(t_token *token_list)
{
	int		i;
	t_token	*aux;
	t_list	*wildcards;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			if ((i == 0 || (i > 0 && ft_strncmp(aux->token[i - 1], "<<", 3)))
				&& ft_strchr_wc(aux->token[i]))
			{
				wildcards = expand_wildcards(aux->token[i]);
				//put_wildcards(&aux->token[i], wildcards);
				free_list(&wildcards);
			}
			i++;
		}
		aux = aux->next;
	}
}
