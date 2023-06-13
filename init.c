/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:30:02 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/13 15:02:14 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	ft_init(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
	{
		printf(E_NB_ARGS);
		data.nb_philo = -1;
		return (data);
	}
	data.nb_philo = ft_atoi(av[1]);
	data.t_die = ft_atoi(av[2]);
	data.t_eat = ft_atoi(av[3]);
	data.t_sleep = ft_atoi(av[4]);
	data.nb_must_eat = 0;
	data.first_philo = NULL;
	gettimeofday(&(data.start_time), NULL);
	data.start_ts = data.start_time.tv_sec + data.start_time.tv_usec;
	if (ac == 6)
		data.nb_must_eat = ft_atoi(av[5]);
	data.fd_log = ft_open_log();
	pthread_mutex_init(&(data.write_mutex), NULL);
	return (data);
}