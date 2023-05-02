/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguler <eguler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:06:40 by eguler            #+#    #+#             */
/*   Updated: 2022/08/01 12:30:59 by eguler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *philo, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < philo->nbrphilo)
		pthread_mutex_destroy(&mutex[i++]);
	free(mutex);
	free(philo->is_ph_dead);
	free(philo->full);
	pthread_mutex_destroy(philo->lock);
	free(philo->lock);
	free(philo);
}

void	deadcheck(t_philo *ph)
{
	while (1)
	{
		pthread_mutex_lock(ph->lock);
		if (*ph->is_ph_dead)
			return ;
		pthread_mutex_unlock(ph->lock);
	}
}

int	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Wrong argument number!\n");
		return (0);
	}
	while (av[i])
	{
		if (is_digit(av[i]) == 0 || ft_atoi(av[i]) <= 0)
		{
			printf("Wrong argument!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	int				size;

	if (check_arg(ac, av) == 0)
		return (0);
	size = ft_atoi(av[1]);
	philo = malloc(sizeof(t_philo) * size);
	mutex = initmutex(size);
	alloandinit(philo, av, mutex);
	createthread(philo, size);
	deadcheck(philo);
	ft_free(philo, mutex);
}
