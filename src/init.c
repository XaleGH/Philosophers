/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:51:51 by asaux             #+#    #+#             */
/*   Updated: 2024/07/24 10:39:59 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	numeric(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (av[j])
	{
		while (av[j][i])
		{
			if (av[j][i] < '0' || av[j][i] > '9' || ft_strlen(av[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	parse_arg(int ac, char **av, t_philo *philo)
{
	if ((ac == 5 || ac == 6) && numeric(av))
	{
		philo->arg.total = ft_atoi(av[1]);
		philo->arg.die = ft_atoi(av[2]);
		philo->arg.eat = ft_atoi(av[3]);
		philo->arg.sleep = ft_atoi(av[4]);
		philo->arg.m_eat = -1;
		if (ac == 6)
			philo->arg.m_eat = ft_atoi(av[5]);
		if (philo->arg.total <= 0 || philo->arg.die <= 0
			|| philo->arg.eat <= 0 || philo->arg.sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}

void	init_mutex(t_philo *philo)
{
	pthread_mutex_init(&philo->arg.write_mutex, NULL);
	pthread_mutex_init(&philo->arg.dead, NULL);
	pthread_mutex_init(&philo->arg.time_eat, NULL);
	pthread_mutex_init(&philo->arg.finish, NULL);
}

void	cleanup(t_philo *philo)
{
	int	i;

	if (philo->thread)
	{
		i = -1;
		while (++i < philo->arg.total)
			pthread_mutex_destroy(&philo->thread[i].l_f);
	}
	pthread_mutex_destroy(&philo->arg.write_mutex);
	pthread_mutex_destroy(&philo->arg.dead);
	pthread_mutex_destroy(&philo->arg.time_eat);
	pthread_mutex_destroy(&philo->arg.finish);
}

int	initialize(t_philo *philo)
{
	int	i;

	i = 0;
	philo->arg.start_t = actual_time();
	philo->arg.stop = 0;
	philo->arg.nb_p_finish = 0;
	init_mutex(philo);
	while (i < philo->arg.total)
	{
		philo->thread[i].id = i + 1;
		philo->thread[i].ms_eat = philo->arg.start_t;
		philo->thread[i].nb_eat = 0;
		philo->thread[i].finish = 0;
		philo->thread[i].r_f = NULL;
		pthread_mutex_init(&philo->thread[i].l_f, NULL);
		if (philo->arg.total == 1)
			return (1);
		if (i == philo->arg.total - 1)
			philo->thread[i].r_f = &philo->thread[0].l_f;
		else
			philo->thread[i].r_f = &philo->thread[i + 1].l_f;
		i++;
	}
	return (1);
}
