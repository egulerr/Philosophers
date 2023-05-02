/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguler <eguler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:51:23 by eguler            #+#    #+#             */
/*   Updated: 2022/08/01 13:44:47 by eguler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gokill(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (!*philo->is_ph_dead)
	{
		printf("\033[0;39m%ld %d is died\n", philo->time_to_start, philo->id);
		*philo->is_ph_dead = 1;
	}
	pthread_mutex_unlock(philo->lock);
}

void	ft_usleep(t_philo *philo, long ms)
{
	long	time;

	get_time(philo);
	time = philo->time_to_start;
	while (philo->time_to_start < time + ms)
	{
		get_time(philo);
		if (philo->time_to_start > philo->death)
			gokill(philo);
		usleep(100);
	}
}

int	is_digit(char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] < '0' || arr[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	get_time(t_philo *ph)
{
	pthread_mutex_lock(ph->lock);
	gettimeofday(&ph->tv, NULL);
	ph->ms = (ph->tv.tv_sec * 1000) + (ph->tv.tv_usec / 1000);
	if (ph->start == 0)
		ph->start = ph->ms;
	ph->time_to_start = (ph->ms) - (ph->start);
	pthread_mutex_unlock(ph->lock);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		neg;
	int		count;

	count = 0;
	num = 0;
	neg = 1;
	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-')
		neg *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] <= 57 && str[i] >= 48))
	{
		num = num * 10 + (str[i] - 48);
		if (num * neg > 2147483647)
			return (0);
		else if (num * neg < -2147483647)
			return (0);
		i++;
	}
	return (num * neg);
}
