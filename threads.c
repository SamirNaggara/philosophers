/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:32:15 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/24 13:00:12 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	On dois creer un thread par philosophe
	Alors on parcours la liste chainée des philosophes
	Et on créé un thread par philosophe
*/
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
/*
	Au moment de creer charque thread
	On dis que le philosophe vient de manger
	Puis on créé le thread
	On le stock ensuite dans la liste chainée
*/

int	ft_create_one_thread(t_philo *philo)
{
	pthread_t	thread;	

	philo->last_eat = ft_get_now_ts();
	pthread_create(&thread, NULL, ft_philo_thread, philo);
	philo->thread = thread;
	return (1);
}
/*
	C'est le thread de chaque philosophe
	Il mange
	Il dors
	Et il essaie de remanger
	Si on sors ça veut dire que quelqu'un n'est plus vivant

*/

void	*ft_philo_thread(void *philo)
{
	t_philo	*actual_philo;
	t_data	*data;

	actual_philo = (t_philo *)philo;
	data = (t_data *)actual_philo->data;
	if (ft_all_finish_eating(data))
		return (NULL);
	ft_first_action(data, actual_philo);
	while (ft_test_is_alive(data))
	{
		if (!ft_go_eat(actual_philo))
			break ;
		if (!ft_go_sleep(actual_philo))
			break ;
	}
	return (NULL);
}
/*
	A la fin tout les threads doivent se rejoindre
	Alors on passe par la liste chainée des philosophes
	Et on les rejoins tous !
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
/*
	En premier, un philosophe essaie de manger s'il est impaire
	Attention si un philosophe est impaire, mais que c'est le dernier,
	on veut pas qu'il mange puisque le premier mange !
	Si il est pair, il va attendre
*/

int	ft_first_action(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		ft_write_in_log(data, philo, L_THINK);
		usleep(data->t_eat * 2);
	}
	return (1);
}
