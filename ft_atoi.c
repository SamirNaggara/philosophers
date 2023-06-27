/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:28:36 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/27 22:10:21 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		resultat;

	i = 0;
	sign = 1;
	resultat = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		resultat = resultat * 10 + nptr[i++] - '0';
	return (sign * resultat);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s % 256 == c % 256)
			return ((char *)s);
		s++;
	}
	if (c % 256 == 0)
		return ((char *)s);
	return ((char *)0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_power(int nb, int power)
{
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	if (power == 1)
		return (nb);
	return ((long)(nb * ft_power(nb, power - 1)));
}
