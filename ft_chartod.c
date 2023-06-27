/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chartod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:29:34 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/27 22:21:59 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Tranforme un char en double
	Useless dans le programme, au debut je pensais
	qu'on devait rentrer des nombres à virgule
	dans les arguments
*/
double	ft_chartod(char *s)
{
	char	*dec_char;
	int		ent;
	int		dec;
	int		nb_dec;

	dec_char = ft_strchr(s, '.');
	if (!dec_char)
		return ((double)ft_atoi(s));
	dec_char++;
	ent = ft_atoi(s);
	dec = ft_atoi(dec_char);
	nb_dec = ft_strlen_nb(dec);
	while (*(dec_char++) == '0')
		nb_dec++;
	return ((double)ent + (double)dec / (double)(ft_power(10, nb_dec)));
}

int	ft_strlen_nb(int nb)
{
	int	len;

	len = 1;
	while (nb / (ft_power(10, len)) != 0)
		len++;
	return (len);
}
