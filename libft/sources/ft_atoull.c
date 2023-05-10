/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:22:35 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/09 21:25:44 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_atoull(const char *nptr)
{
	unsigned long long	num;

	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	num = 0;
	while (ft_isdigit(*nptr) == 1)
	{
		num = num * 10 + (*nptr - 48);
		nptr++;
	}
	return (num);
}
