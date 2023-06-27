/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:30:02 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/27 22:20:15 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	ft_init(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
		return (ft_not_enough_args(data));
	ft_fill_data(&data, ac, av);
	ft_set_initial_time(&data);
	data.fd_log = ft_open_log();
	pthread_mutex_init(&(data.write_mutex), NULL);
	pthread_mutex_init(&(data.alive_mutex), NULL);
	return (data);
}

/*
	On essaie d'ouvrir ou de creer un fichier de log.
	Si ça ne marche pas on envoie le message d'erreur
	Et on met le fd à -1, l'erreur sera récupéré dans le main
*/

int	ft_open_log(void)
{
	int	fd;

	fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		printf(E_LOG);
	return (fd);
}

/*
	On enregistre l'heure de démarrage du programme
*/

void	ft_set_initial_time(t_data *data)
{
	gettimeofday(&(data->start_time), NULL);
	data->start_ts = data->start_time.tv_sec * 1000000
		+ data->start_time.tv_usec;
}

/*
	On remplis toutes les datas avec les arguments
*/

void	ft_fill_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->first_philo = NULL;
	data->e_is_alive = 1;
	data->nb_must_eat = -1;
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
}

t_data	ft_not_enough_args(t_data data)
{
	printf(E_NB_ARGS);
	data.nb_philo = -1;
	return (data);
}
