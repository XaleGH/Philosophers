/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:36:20 by asaux             #+#    #+#             */
/*   Updated: 2024/05/21 16:36:47 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], fd);
		i++;
	}
}

int	ft_atoi(char *nptr)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + nptr[i++] - '0';
	return (res);
}
