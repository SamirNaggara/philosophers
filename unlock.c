/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlock.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:12:43 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/27 22:16:32 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_unlock_fork_and_return(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->fork_mutex));
	pthread_mutex_unlock(&(philo->right->fork_mutex));
	return (0);
}
