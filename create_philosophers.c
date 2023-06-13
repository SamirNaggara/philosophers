/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:31:38 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/13 14:57:28 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_create_philophers(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->nb_philo)
	{
		if (!ft_append_philosopher(data, i++))
		{
			ft_destroy_philosophers(data);
			return (0);
		}
	}
	return (1);
}

void	ft_destroy_philosophers(t_data *data)
{
	t_philo	*tmp;
	if (!data->first_philo)
		return ;
	while (data->first_philo != data->first_philo->left)
	{
		tmp = data->first_philo->left->left;
		pthread_mutex_destroy(&(data->first_philo->left->fork_mutex));
		free(data->first_philo->left);
		data->first_philo->left = tmp;
	}
	free(data->first_philo);

}

int	ft_append_philosopher(t_data *data, int i)
{
	t_philo	*new;

	if (!data->first_philo)
		return (ft_create_first_philo(data));
	new = ft_create_one_philo(data);
	if (!new)
		return (0);
	new->left = data->first_philo->left;
	new->right = data->first_philo;
	new->id = i;
	data->first_philo->left->right = new;
	data->first_philo->left = new;
	return (1);
}

t_philo	*ft_create_one_philo(t_data *data)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (0);
	pthread_mutex_init(&(new->fork_mutex), NULL);
	new->id = 1;
	new->fork = 1;
	new->alive = 1;
	new->data = data;
	new->state = 't';
	new->last_eat = 0;
	return (new);
}

int	ft_create_first_philo(t_data *data)
{
	data->first_philo = ft_create_one_philo(data);
	if (!data->first_philo)
		return (0);
	data->first_philo->left = data->first_philo;
	data->first_philo->right = data->first_philo;
	return (1);
}
