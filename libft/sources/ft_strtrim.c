/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 00:42:28 by byoshimo          #+#    #+#             */
/*   Updated: 2022/09/27 03:28:24 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strtrim_beg(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	i = 0;
	k = 0;
	while (s1[k])
	{
		j = i;
		l = 0;
		while (set[l])
		{
			if (s1[k] == set[l])
			{
				i++;
				break ;
			}
			l++;
		}
		if (j == i)
			break ;
		k++;
	}
	return (i);
}

static size_t	ft_strtrim_end(char const *s1, char const *set, size_t m)
{
	size_t	j;
	size_t	k;
	size_t	l;

	k = ft_strlen(s1) - 1;
	while (k > 0)
	{
		j = m;
		l = 0;
		while (set[l])
		{
			if (s1[k] == set[l])
			{
				m++;
				break ;
			}
			l++;
		}
		if (j == m)
			break ;
		k--;
	}
	return (m);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	m;
	size_t	n;
	char	*str;

	n = ft_strlen(s1);
	m = ft_strtrim_beg(s1, set);
	if (m != ft_strlen(s1))
		n = ft_strtrim_end(s1, set, m);
	str = ft_substr(s1, m, ft_strlen(s1) - n);
	if (str == NULL)
		return (NULL);
	return (str);
}
