/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:21:13 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/14 01:48:43 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_life(t_philo *philo)
{
	while (philo->alive)
	{
		if (!ft_go_eat(philo))
			return (0);
		if (!ft_go_sleep(philo))
			return (0);
	}
	return (1);
}

int	ft_go_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	while (!ft_am_i_dead(data, philo) && ft_they_are_eating(philo))
		;
	if (ft_am_i_dead(data, philo))
		return (0);
	pthread_mutex_lock(&(philo->right->fork_mutex));
	philo->state = 'e';
	if (!ft_write_in_log(data, philo, "Je mange !\n"))
	{
		pthread_mutex_unlock(&(philo->right->fork_mutex));
		return (0);
	}
	usleep(data->t_eat * 1000);
	philo->state = 's';
	pthread_mutex_unlock(&(philo->right->fork_mutex));
	return (1);
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
	if (!ft_test_is_alive(data))
		return (0);
	if (!ft_write_in_log(data, philo, "Je dors !\n"))
		return (0);
	usleep(data->t_sleep * 1000);
	philo->state = 't';
	ft_write_in_log(data, philo, "J'ai bien dormi ! Maintenant je pense\n");
	return (1);
	
}

int	ft_test_is_alive(t_data *data)
{
	pthread_mutex_lock(&(data->alive_mutex));
	if (!data->e_is_alive)
	{
		pthread_mutex_unlock(&(data->alive_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(data->alive_mutex));
	return (1);
}