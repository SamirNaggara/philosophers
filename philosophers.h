/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:15:57 by snaggara          #+#    #+#             */
/*   Updated: 2023/06/14 14:12:19 by snaggara         ###   ########.fr       */
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
# include <stdlib.h>
# include <sys/time.h>



# define E_NB_ARGS "Il n'y a pas assez d'arguments !!\n"
# define E_NO_PHIL "Il faut au moins 1 philosophe... !!\n"
# define E_LOG "Il y a eu un problème avec l'ouverture du fichier de log\n"
# define L_FORK "has taken a fork\n"
# define L_EAT "is eating\n"
# define L_SLEEP "is sleeping\n"
# define L_THINK "is thiking\n"
# define L_DIE "died\n"
# define L_FINISH "On a tous finis de manger\n"



typedef struct s_philo
{
	int				id;
	int				fork;
	pthread_t		thread;
	struct s_philo	*left;
	struct s_philo	*right;
	struct s_data	*data;
	pthread_mutex_t	fork_mutex;
	int				alive;
	char			state;
	pthread_mutex_t	state_mutex;
	long			last_eat;
	int				nb_eat;
	pthread_mutex_t	nb_eat_mutex;


}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_must_eat;
	int				fd_log;
	t_philo			*first_philo;
	pthread_mutex_t	write_mutex;
	struct timeval	start_time;
	long			start_ts;
	int				e_is_alive;
	pthread_mutex_t	alive_mutex;

}	t_data;



t_data	ft_init(int ac, char **av);
double	ft_chartod(char *s);
int		ft_atoi(const char *nptr);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *str);
int		ft_strlen_nb(int nb);
long		ft_power(int nb, int power);
int	ft_write_in_log(t_data *data, t_philo *actual_philo, char *msg);
int	ft_open_log(void);
int	ft_create_philophers(t_data *data);
void	ft_destroy_philosophers(t_data *data);
int	ft_append_philosopher(t_data *data, int i);
t_philo	*ft_create_one_philo(t_data *data);
int	ft_create_first_philo(t_data *data);
int	ft_join_threads(t_data *data);
int	ft_create_threads(t_data *data);
int	ft_create_one_thread(t_philo *philo);
void	*ft_philo_thread(void *dat);
char	*ft_itoa(long n);
char	*ft_initialise_result(long *number, size_t *i, size_t len);
void	*ft_memset(void *s, int c, size_t n);
int	ft_life(t_philo *philo);
int	ft_go_eat(t_philo *philo);
int	ft_go_sleep(t_philo *philo);
int	ft_they_are_eating(t_philo *philo);
int	ft_am_i_dead(t_data *data, t_philo *philo);
int	ft_test_is_alive(t_data *data);
void	ft_change_is_alive(t_data *data, int alive);
long	ft_get_now_ts(void);
int		ft_change_state(t_philo *philo, char c);
char	ft_check_state(t_philo *philo);
int	ft_end_program(t_data *data);
long	ft_get_timestamp_to_display(t_data *data);
int	ft_unlock_write_and_return(t_data *data);
void	ft_write_texte(t_data *data, char *msg, char *id, char *c_ts);
int	ft_first_action(t_data *data, t_philo *philo);
int	ft_increment_nb_eat(t_philo *philo);
int	ft_check_nb_eat(t_philo *philo);
int	ft_finish_eating(t_data *data);
int	ft_unlock_fork_and_return(t_philo *philo);



#endif
