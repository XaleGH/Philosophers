/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:54:59 by root              #+#    #+#             */
/*   Updated: 2024/07/24 11:45:02 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*is_dead(void *data)
{
	t_thread	*ph;

	ph = (t_thread *)data;
	while (!check_death(ph, 0))
	{
		ft_usleep(ph->pa->die + 1);
		pthread_mutex_lock(&ph->pa->time_eat);
		pthread_mutex_lock(&ph->pa->finish);
		if (!check_death(ph, 0) && !ph->finish
			&& ((actual_time() - ph->ms_eat) >= (long)(ph->pa->die)))
		{
			pthread_mutex_unlock(&ph->pa->finish);
			pthread_mutex_unlock(&ph->pa->time_eat);
			pthread_mutex_lock(&ph->pa->write_mutex);
			write_status("died\n", ph);
			pthread_mutex_unlock(&ph->pa->write_mutex);
			check_death(ph, 1);
			return (NULL);
		}
		pthread_mutex_unlock(&ph->pa->finish);
		pthread_mutex_unlock(&ph->pa->time_eat);
	}
	return (NULL);
}

void	*thread(void *data)
{
	t_thread	*ph;

	ph = (t_thread *)data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->pa->eat / 10);
	while (!check_death(ph, 0))
	{
		activity(ph);
		if ((int)++ph->nb_eat == ph->pa->m_eat)
		{
			pthread_mutex_lock(&ph->pa->finish);
			ph->finish = 1;
			ph->pa->nb_p_finish++;
			if (ph->pa->nb_p_finish == ph->pa->total)
			{
				pthread_mutex_unlock(&ph->pa->finish);
				check_death(ph, 2);
				return (NULL);
			}
			pthread_mutex_unlock(&ph->pa->finish);
			return (NULL);
		}
		sleep_think(ph);
	}
	return (NULL);
}

int	threading(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->arg.total)
	{
		philo->thread[i].pa = &philo->arg;
		if (i == 0)
			pthread_create(&philo->thread[i].thread_death_id,
				NULL, is_dead, &philo->thread[i]);
		if (pthread_create(&philo->thread[i].thread_id,
				NULL, thread, &philo->thread[i]) != 0)
			return (ft_exit("Pthread did not return 0\n"));
		i++;
	}
	return (1);
}
