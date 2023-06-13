/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:32:15 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/13 15:07:24 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"




/*
Ta mission si tu l'acceptes
Range tout le fichier threads.c deja
Les morts ne marchent pas, regle ça !
Fais aussi en sorte que les gens puissent mourir pendant leur sommeil, ou alors met une condition au debut pour que ce cas ne soit pas possible
*/
int	ft_join_threads(t_data *data)
{
	t_philo	*browse;
	int		first_lap;

	browse = data->first_philo;
	first_lap = 1;
	while (first_lap || browse != data->first_philo)
	{
		if (first_lap)
			first_lap = 0;
		pthread_join(browse->thread, NULL);

		browse = browse->right;
	}
	return (1);

}

int	ft_create_threads(t_data *data)
{
	t_philo	*browse;
	int		first_lap;

	browse = data->first_philo;
	first_lap = 1;
	while (first_lap || browse != data->first_philo)
	{
		if (first_lap)
			first_lap = 0;
		ft_create_one_thread(browse);
		browse = browse->right;
	}
	return (1);
}

int	ft_create_one_thread(t_philo *philo)
{
	pthread_t	thread;	

	pthread_create(&thread, NULL, ft_philo_thread, philo);
	philo->thread = thread;
	return (1);
}

void	*ft_philo_thread(void *philo)
{
	t_data 	*data;
	t_philo	*actual_philo;
	pthread_t tid;
	
	tid = pthread_self();
	(void)tid;
	actual_philo = (t_philo *)philo;
	data = (t_data *)actual_philo->data;
	ft_write_in_log(data, actual_philo, "Le philosophe entre dans la piece\n");
	ft_start_life(philo);
	return (NULL);
}

int	ft_start_life(t_philo *philo)
{
	while (philo->alive)
	{
		pthread_mutex_lock(&(philo->fork_mutex));
		ft_go_eat(philo);
		pthread_mutex_unlock(&(philo->fork_mutex));
		ft_go_sleep(philo);
	}
	return (1);

}

int	ft_go_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	while (ft_they_are_eating(philo))
		ft_am_i_dead(data, philo);
	pthread_mutex_lock(&(philo->right->fork_mutex));
	philo->state = 'e';
	ft_write_in_log(data, philo, "Je mange !\n");
	usleep(data->t_eat * 1000);
	philo->state = 's';
	pthread_mutex_unlock(&(philo->right->fork_mutex));
	return (1);
}

int	ft_am_i_dead(t_data *data, t_philo *philo)
{
	long			now_ts;
	struct timeval	now;

	gettimeofday(&now, NULL);
	now_ts = (now.tv_sec - data->start_time.tv_sec) * 1000000;
	now_ts += now.tv_usec - data->start_time.tv_usec;

	if (data->start_ts - philo->last_eat > data->t_die)
		return (1);
	return (0);

}

int	ft_they_are_eating(t_philo *philo)
{
	if (philo->right->state == 'e')
		return (1);
	if (philo->left->state == 'e')
		return (1);
	return (0);
}

int	ft_go_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	ft_write_in_log(data, philo, "Je dors !\n");
	usleep(data->t_sleep * 1000);
	philo->state = 't';
	ft_write_in_log(data, philo, "J'ai bien dormi ! Maintenant je pense\n");
	return (1);
	
}