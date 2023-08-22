/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:22:23 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/22 13:12:46 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Si moi j'suis mort, je retourne 0 et un message d'erreur
	Si quelqu'un d'autre, je retourne juste 0
	Si je ne peux pas ecrire, je suis mort
	Puis je dis a tout le monde que je suis mort
*/
int	ft_am_i_dead(t_data *data, t_philo *philo)
{
	if (!ft_test_is_alive(data))
		return (1);
	if (ft_get_now_ts() > philo->last_eat + (long)(data->t_die * 1000))
	{
		if (!ft_write_in_log(data, philo, L_DIE))
			return (1);
		ft_change_is_alive(data, 0);
		return (1);
	}
	return (0);
}

int	ft_test_is_alive(t_data *data)
{
	int	status;

	pthread_mutex_lock(&(data->alive_mutex));
	status = data->e_is_alive;
	pthread_mutex_unlock(&(data->alive_mutex));
	return (status);
}

void	ft_change_is_alive(t_data *data, int alive)
{
	pthread_mutex_lock(&(data->alive_mutex));
	data->e_is_alive = alive;
	pthread_mutex_unlock(&(data->alive_mutex));
}
/*
	Renvoie 1 si tout le monde a assez mangé
	En disant que quelqu'un est mort
	Pour pas que ça continue
*/

int	ft_all_finish_eating(t_data *data)
{
	t_philo	*browse;
	int		first_lap;

	if (data->nb_must_eat < 0)
		return (0);
	browse = data->first_philo;
	first_lap = 1;
	while (first_lap || browse != data->first_philo)
	{
		if (first_lap)
			first_lap = 0;
		if (ft_check_nb_eat(browse) < data->nb_must_eat)
			return (0);
		browse = browse->right;
	}
	ft_write_in_log(data, data->first_philo, L_FINISH);
	ft_change_is_alive(data, 0);
	return (1);
}
