/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 22:12:10 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/22 14:37:56 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_change_fork(t_philo *philo, char c)
{
	pthread_mutex_lock(&(philo->fork_mutex));
	philo->fork = c;
	pthread_mutex_unlock(&(philo->fork_mutex));
	return (1);
}

char	ft_check_fork(t_philo *philo)
{
	char	letter;

	pthread_mutex_lock(&(philo->fork_mutex));
	letter = philo->fork;
	pthread_mutex_unlock(&(philo->fork_mutex));
	return (letter);
}
/*
	EN plus d'incrementer nb_eat
	La fonction renvoie 1 tout le monde a fini de manger
*/

int	ft_increment_nb_eat(t_philo *philo)
{
	int	status;

	status = 1;
	pthread_mutex_lock(&(philo->nb_eat_mutex));
	philo->nb_eat++;
	pthread_mutex_unlock(&(philo->nb_eat_mutex));
	return (status);
}

int	ft_check_nb_eat(t_philo *philo)
{
	int	nb_eat;

	pthread_mutex_lock(&(philo->nb_eat_mutex));
	nb_eat = philo->nb_eat;
	pthread_mutex_unlock(&(philo->nb_eat_mutex));
	return (nb_eat);
}
