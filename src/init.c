/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:51:51 by asaux             #+#    #+#             */
/*   Updated: 2024/07/16 15:51:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_mutex(t_philo *philo)
{
	pthread_mutex_init(&philo->arg.write_mutex, NULL);
	pthread_mutex_init(&philo->arg.dead, NULL);
	pthread_mutex_init(&philo->arg.time_eat, NULL);
	pthread_mutex_init(&philo->arg.finish, NULL);
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
		pthread_mutex_init(&philo->thread->l_f, NULL);
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
