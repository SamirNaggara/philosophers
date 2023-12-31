/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaggara <snaggara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:15:57 by snaggara          #+#    #+#             */
/*   Updated: 2023/08/22 14:37:56 by snaggara         ###   ########.fr       */
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

# define E_NB_ARGS "Not enough args !!\n"
# define E_NO_PHIL "Is a philosopher a philosopher if their is \
no philosopher ? !!\n"
# define E_LOG "Il y a eu un problème avec l'ouverture du fichier de log\n"
# define E_ARGS "Args are not valid, decided the laws of nature\n"
# define L_FORK "has taken a fork\n"
# define L_EAT "\033[1;32mis eating\033[0m \n"
# define L_SLEEP "is sleeping\n"
# define L_THINK "is thiking\n"
# define L_DIE "died\n"
# define L_FINISH "stoped everything. What is the point of eating anyway ?\n"

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	struct s_philo	*left;
	struct s_philo	*right;
	struct s_data	*data;
	int				alive;
	char			fork;
	pthread_mutex_t	fork_mutex;
	long			last_eat;
	int				nb_eat;
	pthread_mutex_t	nb_eat_mutex;
}	t_philo;

typedef struct s_data
{
	long			nb_philo;
	long			t_die;
	long			t_eat;
	long			t_sleep;
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
long	ft_power(int nb, int power);
int		ft_write_in_log(t_data *data, t_philo *actual_philo, char *msg);
int		ft_open_log(void);
int		ft_create_philophers(t_data *data);
int		ft_destroy_philosophers(t_data *data);
int		ft_append_philosopher(t_data *data, int i);
t_philo	*ft_create_one_philo(t_data *data);
int		ft_create_first_philo(t_data *data);
int		ft_join_threads(t_data *data);
int		ft_create_threads(t_data *data);
int		ft_create_one_thread(t_philo *philo);
void	*ft_philo_thread(void *dat);
char	*ft_itoa(long n);
char	*ft_initialise_result(long *number, size_t *i, size_t len);
void	*ft_memset(void *s, int c, size_t n);
int		ft_life(t_philo *philo);
int		ft_go_eat(t_philo *philo);
int		ft_go_sleep(t_philo *philo);
int		ft_they_are_eating(t_philo *philo);
int		ft_am_i_dead(t_data *data, t_philo *philo);
int		ft_test_is_alive(t_data *data);
void	ft_change_is_alive(t_data *data, int alive);
long	ft_get_now_ts(void);
int		ft_change_fork(t_philo *philo, char c);
char	ft_check_fork(t_philo *philo);
int		ft_end_program(t_data *data);
long	ft_get_timestamp_to_display(t_data *data);
int		ft_unlock_write_and_return(t_data *data);
void	ft_write_texte(t_data *data, char *msg, char *id, char *c_ts);
int		ft_first_action(t_data *data, t_philo *philo);
int		ft_increment_nb_eat(t_philo *philo);
int		ft_check_nb_eat(t_philo *philo);
int		ft_all_finish_eating(t_data *data);
t_data	ft_not_enough_args(t_data data);
void	ft_fill_data(t_data *data, int ac, char **av);
void	ft_set_initial_time(t_data *data);
int		ft_error_no_phil(void);
int		ft_take_forks(t_data *data, t_philo *philo);
int		ft_still_sleeping(t_data *data, t_philo *philo);
int		ft_verify_args(int ac, char **av);
int		ft_is_number(char *arg);
t_data	ft_error_args(t_data data);

#endif
