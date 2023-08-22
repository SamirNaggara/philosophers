/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:21:43 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/22 12:11:28 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Si y'a pas de philosophe, ou un nombre negatif
*/
int	ft_error_no_phil(t_data *data)
{
	printf(E_NO_PHIL);
	return (0);
}

/*
	Si l'initialisation ne s'est pas passé correctement, 
	alors soit le nb_philo aura été set à -1 ou le fd du fichier sera de -1.
	Dans ce cas, on ferme le fd et on retourne 0
	Pas grave de close fd_log si il est egal a -1
*/
int	ft_bad_init(t_data *data)
{
	return (0);
}

int	ft_end_program(t_data *data)
{
	ft_destroy_philosophers(data);
	pthread_mutex_destroy(&(data->write_mutex));
	pthread_mutex_destroy(&(data->alive_mutex));
	return (1);
}
