/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_exp_aux_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:04:19 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 19:38:00 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	beg_of_file_name(char *content, char *split_wc_j, int *k)
{
	if (ft_strncmp(content, split_wc_j, ft_strlen(split_wc_j)))
	{
		content[0] = '\0';
		return (0);
	}
	*k += ft_strlen(split_wc_j);
	return (1);
}

static int	middle_of_file_name(char *content, char *split_wc_j,
	int *k, int show_hidden_files)
{
	char	*c;

	c = ft_strnstr(content + *k, split_wc_j, ft_strlen(content));
	if (!c || (!show_hidden_files && c[0] == '.'))
	{
		(content)[0] = '\0';
		return (0);
	}
	*k = (c - content) + ft_strlen(split_wc_j);
	return (1);
}

static int	end_of_file_name(char *content, char *split_wc_j, int k)
{
	if (ft_strlen(split_wc_j) > ft_strlen(content + k)
		|| ft_strncmp(content + ft_strlen(content)
			- ft_strlen(split_wc_j), split_wc_j, ft_strlen(split_wc_j)))
	{
		content[0] = '\0';
		return (0);
	}
	return (1);
}

static void	try_find_split(char *token_i, char **split_wc,
	t_list *files, int show_hidden_files)
{
	int		j;
	int		k;
	int		length;

	length = ft_strlen(token_i);
	j = 0;
	k = 0;
	while (split_wc[j])
	{	
		if (j == 0 && token_i[0] != WILDCARDS)
		{
			if (!beg_of_file_name((char *)files->content, split_wc[j], &k))
				break ;
		}
		else if ((!split_wc[j + 1] && token_i[length - 1] != WILDCARDS))
		{
			if (!end_of_file_name((char *)files->content, split_wc[j], k))
				break ;
		}
		else if (!middle_of_file_name((char *)files->content,
				split_wc[j], &k, show_hidden_files))
			break ;
		j++;
	}
}

void	aux_get_wildcards(char *token_i, t_list *files)
{
	int		show_hidden_files;
	char	**split_wc;
	t_list	*aux_files;

	split_wc = ft_split(token_i, WILDCARDS);
	if (!split_wc[0])
	{
		free(split_wc);
		split_wc = (char **)ft_calloc(2, sizeof(char *));
		split_wc[0] = (char *)ft_calloc(1, sizeof(char));
		show_hidden_files = 0;
	}
	else
		show_hidden_files = 1;
	aux_files = files;
	while (aux_files)
	{
		try_find_split(token_i, split_wc, aux_files, show_hidden_files);
		aux_files = aux_files->next;
	}
	free_ptrptr(split_wc);
}
