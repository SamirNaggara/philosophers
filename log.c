/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:30:56 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/22 14:14:38 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_write_in_log(t_data *data, t_philo *actual_philo, char *msg)
{
	char	*id_philo;
	char	*char_timestamp;

	if (!ft_test_is_alive(data))
		return (0);
	pthread_mutex_lock(&(data->write_mutex));
	char_timestamp = ft_itoa(ft_get_timestamp_to_display(data));
	if (!char_timestamp)
		return (ft_unlock_write_and_return(data));
	id_philo = ft_itoa(actual_philo->id);
	if (!id_philo)
	{
		free(char_timestamp);
		return (ft_unlock_write_and_return(data));
	}
	if (!ft_test_is_alive(data))
	{
		free(char_timestamp);
		free(id_philo);
		return (ft_unlock_write_and_return(data));
	}
	ft_write_texte(data, msg, id_philo, char_timestamp);
	pthread_mutex_unlock(&(data->write_mutex));
	free(char_timestamp);
	return (free(id_philo), 1);
}

void	ft_write_texte(t_data *data, char *msg, char *id, char *c_ts)
{
	write(data->fd_log, c_ts, ft_strlen(c_ts));
	write(data->fd_log, "ms philosopher ", 15);
	write(data->fd_log, id, ft_strlen(id));
	write(data->fd_log, " ", 1);
	write(data->fd_log, msg, ft_strlen(msg));
}

int	ft_unlock_write_and_return(t_data *data)
{
	pthread_mutex_unlock(&(data->write_mutex));
	return (0);
}

long	ft_get_timestamp_to_display(t_data *data)
{
	struct timeval	now;
	long			timestamp;

	gettimeofday(&now, NULL);
	timestamp = (now.tv_sec - data->start_time.tv_sec) * 1000000;
	timestamp += now.tv_usec - data->start_time.tv_usec;
	timestamp /= 1000;
	return (timestamp);
}
