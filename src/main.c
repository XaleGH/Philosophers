/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:18:36 by asaux             #+#    #+#             */
/*   Updated: 2024/07/17 18:10:03 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_death(t_thread *ph, int i)
{
	pthread_mutex_lock(&ph->pa->dead);
	if (i)
		ph->pa->stop = i;
	if (ph->pa->stop)
	{
		pthread_mutex_unlock(&ph->pa->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->pa->dead);
	return (0);
}

int	check_death2(t_philo *p)
{
	pthread_mutex_lock(&p->arg.dead);
	if (p->arg.stop)
	{
		pthread_mutex_unlock(&p->arg.dead);
		return (1);
	}
	pthread_mutex_unlock(&p->arg.dead);
	return (0);
}

int	ft_exit(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

void	stop(t_philo *p)
{
	int	i;
	
	i = -1;
	while (!check_death2(p))
		ft_usleep(1);
	while (++i < p->arg.total)
		pthread_join(p->thread[i].thread_id, NULL);
	pthread_mutex_destroy(&p->arg.write_mutex);
	i = -1;
	while (++i < p->arg.total)
		pthread_mutex_destroy(&p->thread[i].l_f);
	if (p->arg.stop == 2)
		printf("Each philosopher ate %d time(s)\n", p->arg.m_eat);
	free(p->thread);
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (!(parse_arg(ac, av, &philo)))
		return (ft_exit("Invalid Arguments\n"));
	philo.thread = malloc(sizeof(t_thread) * philo.arg.total);
	if (!philo.thread)
		return (ft_exit("Error with malloc\n"));
	if (!initialize(&philo) || !threading(&philo))
	{
		free(philo.thread);
		return (0);
	}
	stop(&philo);
}