/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:59:01 by asaux             #+#    #+#             */
/*   Updated: 2024/05/22 18:37:12 by asaux            ###   ########.fr       */
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
	int			total;
	int			die;
	int			eat;
	int			sleep;
	int			m_eat;
}	t_arg;

typedef struct s_thread
{
	int				id;
	pthread_t		thread_id;
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
int		ft_strlen(char *str);
void	ft_putchar(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
int		ft_atoi(char *nptr);

//error.c
int		ft_error(char *str);

//main.c
int		numeric(char **av);
int		parse_arg(int ac, char **av, t_philo *philo);








#endif

//https://github.com/iciamyplant