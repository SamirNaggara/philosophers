/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:30:56 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/13 15:05:00 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_write_in_log(t_data *data, t_philo *actual_philo, char *msg)
{
	char			*id_philo;
	struct timeval	now;
	char 			*char_timestamp;
	long			timestamp;

	pthread_mutex_lock(&(data->write_mutex));
	gettimeofday(&now, NULL);
	
	timestamp = (now.tv_sec - data->start_time.tv_sec) * 1000000;
	timestamp += now.tv_usec - data->start_time.tv_usec;
	timestamp /= 1000;
	if (actual_philo->state == 'e')
		actual_philo->last_eat = timestamp;
	char_timestamp = ft_itoa(timestamp);
	if (!char_timestamp)
		return (0);
	id_philo = ft_itoa(actual_philo->id);
	if (!id_philo)
		return (0);
	write(data->fd_log, char_timestamp, ft_strlen(char_timestamp));
	write(data->fd_log, " -> ", 5);

	write(data->fd_log, "Philosophe ", 11);
	write(data->fd_log, id_philo, ft_strlen(id_philo) + 1);
	write(data->fd_log, " : ", 4);
	write(data->fd_log, msg, ft_strlen(msg) + 1);
	pthread_mutex_unlock(&(data->write_mutex));
	return (1);
}

int	ft_open_log(void)
{
	int	fd;

	fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		printf(E_LOG);
	return (fd);
}