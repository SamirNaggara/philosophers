/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:21:13 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/23 19:34:17 by snaggara         ###   ########.fr       */
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
		usleep(10);
	if (ft_am_i_dead(data, philo))
		return (0);
	ft_change_fork(philo, 'e');
	if (!ft_take_forks(data, philo))
		return (0);
	if (!ft_write_in_log(data, philo, L_EAT))
		return (0);
	philo->last_eat = ft_get_now_ts();
	usleep(data->t_eat * 1000);
	ft_change_fork(philo, 's');
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
	if (!ft_write_in_log(data, philo, L_FORK))
		status = 0;
	if (!ft_write_in_log(data, philo, L_FORK))
		status = 0;
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
	if (ft_check_fork(philo->right) == 'e')
		return (1);
	if (ft_check_fork(philo->left) == 'e')
		return (1);
	if (ft_get_now_ts() < philo->data->start_ts
		+ 2 * (long)(philo->data->t_eat * 1000))
		return (0);
	if (ft_get_now_ts() - (long)(philo->last_eat) <
			2 * (long)(philo->data->t_eat * 1000) + 10000)
	{
		// printf("Philo %d : Je mange pas, je laisse la place", philo->id);
		// printf("Je retourne 1\nD : %ld\n2 * last eat %ld\n", ft_get_now_ts() - (long)(philo->last_eat), 
		// 	2 * (long)(philo->data->t_eat * 1000) + 10000);
		//ft_write_in_log(philo->data, philo, "Je rentre dans le truc\n");
		return (1);
	}
	// printf("Je retourne 0\nD : %ld\n2 * last eat %ld\n", ft_get_now_ts() - (long)(philo->last_eat), 
	// 2 * (long)(philo->data->t_eat * 1000 + 200));

	return (0);
}

//now - ls_eat > 2 * (long)(philo->data->t_eat * 1000000)



int	ft_go_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (!ft_still_sleeping(data, philo))
		return (0);
	ft_change_fork(philo, 't');
	//usleep(data->t_eat / 3); // A supprimer je pense
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
	long	start_sleep;

	start_sleep = ft_get_now_ts();
	while (!ft_am_i_dead(data, philo) && start_sleep
		+ data->t_sleep * 1000 > ft_get_now_ts())
		usleep(10);
	if (ft_am_i_dead(data, philo))
		return (0);
	return (1);
}
