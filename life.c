/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:21:13 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/27 22:19:05 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Voila le philosopher si essaie de manger
	Il boucle tant qu'il est pas mort et qu'il mange

*/
int	ft_go_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	while (!ft_am_i_dead(data, philo) && ft_they_are_eating(philo))
		;
	if (ft_am_i_dead(data, philo))
		return (0);
	ft_change_state(philo, 'e');
	if (!ft_take_forks(data, philo))
		return (0);
	if (!ft_write_in_log(data, philo, L_EAT))
		return (0);
	philo->last_eat = ft_get_now_ts();
	usleep(data->t_eat * 1000);
	ft_change_state(philo, 's');
	if (!ft_write_in_log(data, philo, L_SLEEP))
		return (0);
	ft_increment_nb_eat(philo);
	if (ft_all_finish_eating(philo->data))
		return (0);
	return (1);
}
/*
	Prends les 2 fourchettes, une par une !
	Si l'écriture ne marche pas, on return 0
	En s'assurant d'avoir bien libéré les mutexs des forks
*/

int	ft_take_forks(t_data *data, t_philo *philo)
{
	int	status;

	status = 1;
	pthread_mutex_lock(&(philo->fork_mutex));
	if (!ft_write_in_log(data, philo, L_FORK))
		status = 0;
	pthread_mutex_unlock(&(philo->fork_mutex));
	pthread_mutex_lock(&(philo->right->fork_mutex));
	if (!ft_write_in_log(data, philo, L_FORK))
		status = 0;
	pthread_mutex_unlock(&(philo->right->fork_mutex));
	return (status);
}
/*
	Vérifie si les vosins mange
	SI je suis mon propre voisin, je considere que je mange
	Parce que je ne peux pas prendre une deuxieme fois
	Ma propre fourchette
*/

int	ft_they_are_eating(t_philo *philo)
{
	if (philo == philo->right)
		return (1);
	if (ft_check_state(philo->right) == 'e')
		return (1);
	if (ft_check_state(philo->left) == 'e')
		return (1);
	return (0);
}

int	ft_go_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (!ft_still_sleeping(data, philo))
		return (0);
	ft_change_state(philo, 't');
	usleep(data->t_eat / 3);
	ft_write_in_log(data, philo, L_THINK);
	return (1);
}
/*
	Still sleeping va dormir le temps désiré.
	Si on en sort parce qu'on est mort on renvoie 0
	Sinon on renvoie 1
*/

int	ft_still_sleeping(t_data *data, t_philo *philo)
{
	int	start_sleep;

	start_sleep = ft_get_now_ts();
	while (!ft_am_i_dead(data, philo) && start_sleep
		+ data->t_sleep * 1000 > ft_get_now_ts())
		;
	if (ft_am_i_dead(data, philo))
		return (0);
	return (1);
}
