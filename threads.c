/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:32:15 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/14 02:05:41 by snaggara         ###   ########.fr       */
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

/*
	Ta mission si tu l'acceptes :

	Ici il y a une fonction fet_get now ts, pour avoir le timestamp de maintenant maintenant.
	On demande souvent ça, donc faut le mettre en fonction et remplacer aussi ailleurs.
	Puis la on va pouvoir au debut du thread mettre le temps de départ comme dernier moment ou ils ont mangé.
	Ca m'amene une question...
	Ce qui nous interesse au fond, c'est pas l'heure ou a commencé leur dernier repas, mais plutot celui ou ils l'ont terminé non ?
	Je te laisse checker ça, je vais dormir je suis épuisé.
	Travaille bien
*/
int	ft_create_one_thread(t_philo *philo)
{
	pthread_t	thread;	

	philo->last_eat = ft_get_now_ts();
	pthread_create(&thread, NULL, ft_philo_thread, philo);
	philo->thread = thread;
	return (1);
}

void	*ft_philo_thread(void *philo)
{
	t_philo *actual_philo;
	t_data	*data;

	actual_philo = (t_philo *)philo;
	data = (t_data *)actual_philo->data;
	if (!ft_test_is_alive(data))
		return (0);
	while (actual_philo->alive)
	{
		if (!ft_go_eat(actual_philo))
			return (NULL);
		if (!ft_go_sleep(actual_philo))
			return (NULL);
	}
	return (NULL);
}







