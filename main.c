/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:43:09 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/12 15:39:58 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	data = ft_init(ac, av);
	if (data.nb_philo == -1 || data.fd_log == -1)
	{
		close(data.fd_log);
		return (0);
	}
	if (data.nb_philo <= 0)
	{
		printf(E_NO_PHIL);
		close(data.fd_log);
		return (0);
	}

	printf("Voila le nb philo %d %f %f %f %d\n", data.nb_philo, data.t_die, data.t_eat, data.t_sleep, data.nb_must_eat);

	ft_create_philophers(data);
	if (data.nb_philo == 1)
	{

		ft_one_philo_guy(&data);
	}


	close(data.fd_log);
	return (0);
}

/*
	Tu t'es arreté ici Samir, tu as construit une belle liste chainéee des familles pour stocké les philosophers...
	Mais...
	Tu ne l'as pas testé, va y avoir pleins d'erreurs xD
	Good luck
*/

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
}

void	ft_destroy_philosophers(t_data *data)
{
	t_philo	*tmp;

	while (data->first_philo == data->first_philo->left)
	{
		tmp = data->first_philo->left->left;
		free(data->first_philo);
		first_philo->left = tmp;
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
	first_philo->left->right = new;
	first_philo->left = new;
	return (1);

}

t_philo	*ft_create_one_philo(t_data *data)
{
	t_philo	*new;

	new->first_philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new->first_philo)
		return (0);
	new->first_philo->id = 1;
	new->first_philo->fork = 1;
	return (1);
}

int	ft_create_first_philo(t_data *data)
{
	data->first_philo = ft_create_one_philo(data),
	if (!data->first_philo)
		return (0);
	data->first_philo->left = data->first_philo;
	data->first_philo->fork = data->first_philo;
	return (1);
}

int	ft_one_philo_guy(t_data *data)
{
	pthread_t	philo1;	

	pthread_create(&philo1, NULL, ft_one_philo_thread, data);

	pthread_join(philo1, NULL);

	return (1);
}

void	*ft_one_philo_thread(void *dat)
{
	t_data *data;

	data = (t_data *)dat;
	ft_write_in_log(data, "Le philosophe numero 1 entre dans la piece\n");
	return (NULL);
}

void	ft_write_in_log(t_data *data, char *msg)
{
	write(data->fd_log, msg, ft_strlen(msg));
}

t_data	ft_init(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
	{
		printf(E_NB_ARGS);
		data.nb_philo = -1;
		return (data);
	}
	data.nb_philo = ft_atoi(av[1]);
	data.t_die = ft_chartod(av[2]);
	data.t_eat = ft_chartod(av[3]);
	data.t_sleep = ft_chartod(av[4]);
	data.nb_must_eat = 0;
	data.first_philo = NULL;
	if (ac == 6)
		data.nb_must_eat = ft_atoi(av[5]);
	data.fd_log = ft_open_log();
	return (data);

}

int	ft_open_log(void)
{
	int	fd;

	fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		printf(E_LOG);
	return (fd);

}

/*
	Tranforme un char en double
	
*/
double	ft_chartod(char *s)
{
	char	*dec_char;
	int		ent;
	int		dec;
	int		nb_dec;

	dec_char = ft_strchr(s, '.');
	if (!dec_char)
		return ((double)ft_atoi(s));
	dec_char++;
	ent = ft_atoi(s);
	dec = ft_atoi(dec_char);
	nb_dec = ft_strlen_nb(dec);
	while (*(dec_char++) == '0')
		nb_dec++;
	return ((double)ent + (double)dec / (double)(ft_power(10, nb_dec)));
	
}

int	ft_strlen_nb(int nb)
{
	int len;

	len = 1;
	while (nb / (ft_power(10, len)) != 0)
		len++;
	return (len);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		resultat;

	i = 0;
	sign = 1;
	resultat = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		resultat = resultat * 10 + nptr[i++] - '0';
	return (sign * resultat);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s % 256 == c % 256)
			return ((char *)s);
		s++;
	}
	if (c % 256 == 0)
		return ((char *)s);
	return ((char *)0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_power(int nb, int power)
{
	if (power <= 0)
		return (0);
	if (power == 1)
		return (nb);
	return ((long)(nb * ft_power(nb, power - 1)));
}