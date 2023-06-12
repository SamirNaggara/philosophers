/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:15:57 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/12 15:20:09 by snaggara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdarg.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>



# define E_NB_ARGS "Il n'y a pas assez d'arguments !!\n"
# define E_NO_PHIL "Il faut au moins 1 philosophe... !!\n"
# define E_LOG "Il y a eu un problème avec l'ouverture du fichier de log\n"

typedef struct s_philo
{
	int		id;
	int		fork;
}	t_philo;

typedef struct s_data
{
	int			nb_philo;
	double		t_die;
	double		t_eat;
	double		t_sleep;
	int			nb_must_eat;
	int			fd_log;
	t_philo		*first_philo;
}	t_data;


t_data	ft_init(int ac, char **av);
double	ft_chartod(char *s);
int		ft_atoi(const char *nptr);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *str);
int		ft_strlen_nb(int nb);
long		ft_power(int nb, int power);
int	ft_one_philo_guy(t_data *data);
void	*ft_one_philo_thread(void *data);
void	ft_write_in_log(t_data *data, char *msg);
int	ft_open_log(void);

#endif
