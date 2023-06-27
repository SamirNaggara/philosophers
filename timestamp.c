/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:09:56 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/27 22:14:00 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
	Pour avoir le timestamp dans un long
*/
long	ft_get_now_ts(void)
{
	long			timestamp;
	struct timeval	now;

	gettimeofday(&now, NULL);
	timestamp = now.tv_sec * 1000000 + now.tv_usec;
	return (timestamp);
}
