/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:22:23 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/14 02:01:52 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_am_i_dead(t_data *data, t_philo *philo)
{
	long			now_ts;
	struct timeval	now;

	if (!ft_test_is_alive(data))
		return (0);
	gettimeofday(&now, NULL);
	now_ts = now.tv_sec * 1000000;
	now_ts += now.tv_usec;
	printf("%ld > %ld\n", now_ts, (long)(data->t_die * 1000));
	if (now_ts - philo->last_eat > (long)(data->t_die * 1000))
	{
		if (!ft_write_in_log(data, philo, "Au revoiiiiir\n"))
			return (1);
		pthread_mutex_lock(&(data->alive_mutex));
		data->e_is_alive = 0;
		pthread_mutex_unlock(&(data->alive_mutex));
		return (1);
	}
	return (0);

}