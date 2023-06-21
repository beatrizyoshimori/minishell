/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:22:35 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/21 20:05:18 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_atoull(const char *nptr)
{
	int					flag;
	unsigned long long	nb;

	flag = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+')
		flag = 1;
	else if (*nptr == '-')
		flag = -1;
	if (flag)
		nptr++;
	nb = 0;
	while (ft_isdigit(*nptr))
	{
		nb = nb * 10 + (*nptr - 48);
		if ((flag != -1 && nb > LL_MAX) || nb > (unsigned long long)LL_MAX + 1)
			return ((unsigned long long)LL_MAX + 2);
		nptr++;
	}
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr && !ft_isdigit(*nptr))
		return ((unsigned long long)LL_MAX + 2);
	return (nb);
}
