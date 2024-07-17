/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:59:01 by asaux             #+#    #+#             */
/*   Updated: 2024/07/17 18:07:31 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_arg
{
	int						total;
	int						die;
	int						eat;
	int						sleep;
	int						m_eat;
	long int				start_t;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_eat;
	pthread_mutex_t			finish;
	int						nb_p_finish;
	int						stop;
}	t_arg;

typedef struct s_thread
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*r_f;
	pthread_mutex_t			l_f;
	t_arg					*pa;
	long int				ms_eat;
	unsigned int			nb_eat;
	int						finish;
}	t_thread;

typedef struct s_philo
{
	t_thread	*thread;
	t_arg		arg;
}	t_philo;

//utils.c
int			ft_strlen(char *str);
void		ft_putchar(char c, int fd);
void		ft_putstr_fd(char *str, int fd);
int			ft_atoi(char *nptr);

//main.c
int			check_death(t_thread *ph, int i);
int			check_death2(t_philo *p);
int			ft_exit(char *str);
void		stop(t_philo *p);
int			main(int ac, char **av);

//init.c
int			numeric(char **av);
int			parse_arg(int ac, char **av, t_philo *philo);
void		init_mutex(t_philo *philo);
int			initialize(t_philo *philo);

//activity.c
void		write_status(char *str, t_thread *ph);
void		sleep_think(t_thread *ph);
void		activity(t_thread *ph);

//threads.c
void		*is_dead(void *data);
void		*thread(void *data);
int			threading(t_philo *philo);

//time.c
long int	actual_time();
void		ft_usleep(long int time_in_ms);

#endif