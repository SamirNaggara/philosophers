/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:41:34 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/28 13:42:27 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Verfifie que tout les arguments sont bien des nombres
*/

int	ft_verify_args(int ac, char **av)
{
	int	status;

	status = 1;
	if (!ft_is_number(av[1]))
		status = 0;
	if (!ft_is_number(av[2]))
		status = 0;
	if (!ft_is_number(av[3]))
		status = 0;
	if (!ft_is_number(av[4]))
		status = 0;
	if (ac >= 6 && !ft_is_number(av[5]))
		status = 0;
	return (status);
}

int	ft_is_number(char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(arg);
	while (i < len)
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

t_data	ft_not_enough_args(t_data data)
{
	printf(E_NB_ARGS);
	data.nb_philo = -1;
	return (data);
}

t_data	ft_error_args(t_data data)
{
	printf(E_ARGS);
	data.nb_philo = -1;
	return (data);
}
