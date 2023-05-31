/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:22:35 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/31 18:30:55 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_atoull(const char *nptr)
{
	int					flag;
	unsigned long long	num;

	flag = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+')
		flag = 1;
	else if (*nptr == '-')
		flag = -1;
	if (flag)
		nptr++;
	num = 0;
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + (*nptr - 48);
		if ((flag != -1 && num > LL_MAX)
			|| num > (unsigned long long)LL_MAX + 1)
			return ((unsigned long long)LL_MAX + 2);
		nptr++;
	}
	if (*nptr && !ft_isdigit(*nptr))
		return ((unsigned long long)LL_MAX + 2);
	return (num);
}
