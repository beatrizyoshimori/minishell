/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 00:34:05 by byoshimo          #+#    #+#             */
/*   Updated: 2022/09/18 00:34:08 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_str(char *num, int n, int aux, int i)
{
	if (num == NULL)
		return (NULL);
	else if (n == 0)
		num[0] = '0';
	else if (n > 0)
		aux = n;
	else
	{
		if (n == -2147483648)
		{
			num[10] = '8';
			aux = -(n / 10);
			i--;
		}
		else
			aux = -n;
		num[0] = '-';
	}
	while (aux != 0)
	{
		num[i - 1] = (aux % 10) + 48;
		aux /= 10;
		i--;
	}
	return (num);
}

char	*ft_itoa(int n)
{
	int		i;
	int		aux;
	char	*num;

	aux = n;
	if (n == 0)
		i = 1;
	else
	{
		i = 0;
		while (aux != 0)
		{
			aux /= 10;
			i++;
		}
		if (n < 0)
			i++;
	}
	num = malloc(i + 1);
	num[i] = '\0';
	ft_itoa_str(num, n, aux, i);
	return (num);
}
