/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:21:13 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/14 14:12:37 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_go_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	while (!ft_am_i_dead(data, philo) && ft_they_are_eating(philo))
		;
	pthread_mutex_lock(&(philo->fork_mutex));
	pthread_mutex_lock(&(philo->right->fork_mutex));
	if (!ft_write_in_log(data, philo, L_FORK))
		return (ft_unlock_fork_and_return(philo));

	ft_change_state(philo, 'e');
	philo->state = 'e';
	if (!ft_write_in_log(data, philo, L_EAT))
		return (ft_unlock_fork_and_return(philo));
	usleep(data->t_eat * 1000);
	ft_increment_nb_eat(philo);
	if (!ft_finish_eating(philo->data))
		return (ft_unlock_fork_and_return(philo));
	ft_change_state(philo, 's');
	philo->last_eat = ft_get_now_ts();
	pthread_mutex_unlock(&(philo->fork_mutex));
	pthread_mutex_unlock(&(philo->right->fork_mutex));
	return (1);
}



int	ft_they_are_eating(t_philo *philo)
{
	if (ft_check_state(philo->right) == 'e')
		return (1);
	if (ft_check_state(philo->left) == 'e')
		return (1);
	return (0);
}

int	ft_change_state(t_philo *philo, char c)
{
	pthread_mutex_lock(&(philo->state_mutex));
	philo->state = c;
	pthread_mutex_unlock(&(philo->state_mutex));
	return (1);
}

char	ft_check_state(t_philo *philo)
{
	char	letter;

	pthread_mutex_lock(&(philo->state_mutex));
	letter = philo->state;
	pthread_mutex_unlock(&(philo->state_mutex));
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

int	ft_go_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (!ft_test_is_alive(data))
		return (0);
	if (!ft_write_in_log(data, philo, L_SLEEP))
		return (0);
	usleep(data->t_sleep * 1000);
	ft_change_state(philo, 't');
	philo->state = 't';
	ft_write_in_log(data, philo, L_THINK);
	return (1);
	
}

