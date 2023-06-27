/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:28:49 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/27 22:11:06 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*ft_itoa(long n)
{
	char	*result;
	long	number;
	size_t	i;
	size_t	len;

	i = 0;
	number = (long)n;
	len = (size_t)ft_strlen_nb(number);
	result = ft_initialise_result(&number, &i, len);
	if (!result)
		return (NULL);
	while (len > 0)
	{
		result[i] = number / (ft_power(10, len - 1)) + '0';
		number = number % (ft_power(10, len - 1));
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_initialise_result(long *number, size_t *i, size_t len)
{
	char	*result;

	if (*number < 0)
	{
		result = (char *)malloc(sizeof(char) * (len + 2));
		if (!result)
			return (NULL);
		ft_memset(result, 0, len + 2);
		result[*i] = '-';
		*number = *number * -1;
		*i = *i + 1;
	}
	else
	{
		result = (char *)malloc(sizeof(char) * (len + 1));
		if (!result)
			return (NULL);
		ft_memset(result, 0, len + 1);
	}
	return (result);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*sbis;

	sbis = (char *)s;
	i = 0;
	while (i < n)
	{
		sbis[i] = c;
		i++;
	}
	return (sbis);
}
