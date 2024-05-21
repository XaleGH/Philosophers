/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:18:36 by asaux             #+#    #+#             */
/*   Updated: 2024/05/21 17:00:54 by asaux            ###   ########.fr       */
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
		j++;
	}
	return (1);
}

int	parse_arg(int ac, char **av, t_philo *philo)
{
	if (ac == 5 || ac == 6 && numeric(av))
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


int	main(int ac, char **av)
{
	t_philo	philo;

	if (!(parse_arg(ac, av, &philo)))
		return (ft_error("Invalid Arguments"));
	philo.thread = malloc(sizeof(t_thread) * philo.arg.total);
}