/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:35:32 by root              #+#    #+#             */
/*   Updated: 2024/07/23 20:27:59 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_status(char *str, t_thread *ph)
{
	long int	time;

	time = -1;
	time = actual_time() - ph->pa->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(ph, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", ph->id, str);
	}
}

void	sleep_think(t_thread *ph)
{
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is sleeping 💤\n", ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	ft_usleep(ph->pa->sleep);
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is thinking 💭\n", ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
}

void	activity(t_thread *ph)
{
	if (!ph->r_f)
	{
		ft_usleep(ph->pa->die * 2);
		return ;
	}
	take_forks(ph);
	pthread_mutex_lock(&ph->pa->write_mutex);
	write_status("is eating 🍝\n", ph);
	pthread_mutex_unlock(&ph->pa->write_mutex);
	pthread_mutex_lock(&ph->pa->time_eat);
	ph->ms_eat = actual_time();
	pthread_mutex_unlock(&ph->pa->time_eat);
	ft_usleep(ph->pa->eat);
	put_forks(ph);
}

void take_forks(t_thread *ph)
{
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(&ph->l_f);
		pthread_mutex_lock(&ph->pa->write_mutex);
		write_status("has taken a fork 🍴\n", ph);
		pthread_mutex_unlock(&ph->pa->write_mutex);
		pthread_mutex_lock(ph->r_f);
		pthread_mutex_lock(&ph->pa->write_mutex);
		write_status("has taken a fork 🍴\n", ph);
		pthread_mutex_unlock(&ph->pa->write_mutex);
	}
	else
	{
		pthread_mutex_lock(ph->r_f);
		pthread_mutex_lock(&ph->pa->write_mutex);
		write_status("has taken a fork 🍴\n", ph);
		pthread_mutex_unlock(&ph->pa->write_mutex);
		pthread_mutex_lock(&ph->l_f);
		pthread_mutex_lock(&ph->pa->write_mutex);
		write_status("has taken a fork 🍴\n", ph);
		pthread_mutex_unlock(&ph->pa->write_mutex);
	}
}

void put_forks(t_thread *ph)
{
	if (ph->id % 2 == 0)
	{
		pthread_mutex_unlock(&ph->l_f);
		pthread_mutex_unlock(ph->r_f);
	}
	else
	{
		pthread_mutex_unlock(ph->r_f);
		pthread_mutex_unlock(&ph->l_f);
	}
}