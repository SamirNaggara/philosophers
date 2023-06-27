/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:43:09 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/27 22:13:28 by snaggara         ###   ########.fr       */
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
		return (ft_bad_init(&data));
	if (data.nb_philo <= 0)
		return (ft_error_no_phil(&data));
	if (!ft_create_philophers(&data))
		return (0);
	ft_create_threads(&data);
	ft_join_threads(&data);
	ft_end_program(&data);
	return (0);
}
