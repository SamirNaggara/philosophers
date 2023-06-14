/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:43:09 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/14 14:14:49 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/*
	Premiere mission Samir...
	Tout ranger...
	Courage, ça va te remettre les pieds dans le projet !
*/
int	main(int ac, char **av)
{
	t_data	data;

	data = ft_init(ac, av);
	if (data.nb_philo == -1 || data.fd_log == -1)
	{
		close(data.fd_log);
		return (0);
	}
	if (data.nb_philo <= 0)
	{
		printf(E_NO_PHIL);
		close(data.fd_log);
		return (0);
	}
	if (!ft_create_philophers(&data))
		return (0);
	ft_create_threads(&data);
	ft_join_threads(&data);
	ft_end_program(&data);
	return (0);
}


int	ft_end_program(t_data *data)
{
	ft_destroy_philosophers(data);
	close(data->fd_log);
	pthread_mutex_destroy(&(data->write_mutex));
	pthread_mutex_destroy(&(data->alive_mutex));
	return (1);
}
