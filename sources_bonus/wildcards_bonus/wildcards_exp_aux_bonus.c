/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_exp_aux_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:04:19 by lucade-s          #+#    #+#             */
/*   Updated: 2023/06/13 17:29:52 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	aux_get_wildcards(char *token_i, t_list *files)
{
	int		j;
	int		k;
	int		length;
	int		show_hidden_files;
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
		show_hidden_files = 0;
	}
	else
		show_hidden_files = 1;
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
			else if ((!split_wc[j + 1] && token_i[length - 1] != WILDCARDS))
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
				if (!c || (!show_hidden_files && c[0] == '.'))
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
