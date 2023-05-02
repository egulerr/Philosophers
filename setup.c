/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguler <eguler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:44:58 by eguler            #+#    #+#             */
/*   Updated: 2022/08/01 12:22:34 by eguler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	createthread(t_philo *philo, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_create(&philo[i].thread, NULL, (void *)&routine, &philo[i]);
		pthread_detach(philo[i].thread);
		i += 2;
	}
	usleep(600);
	i = 1;
	while (i < size)
	{
		pthread_create(&philo[i].thread, NULL, (void *)&routine, &philo[i]);
		pthread_detach(philo[i].thread);
		i += 2;
	}
}

void	createphilo(t_philo *philo, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].nbrphilo = ft_atoi(av[1]);
		philo[i].timetodie = ft_atoi(av[2]);
		philo[i].timetoeat = ft_atoi(av[3]);
		philo[i].timetosleep = ft_atoi(av[4]);
		philo[i].time_to_start = 0;
		philo[i].death = ft_atoi(av[2]);
		philo[i].eatcount = 0;
		philo[i].howmanyeat = -1;
		if (av[5])
			philo[i].howmanyeat = ft_atoi(av[5]);
		i++;
	}
}

void	alloandinit(t_philo *philo, char **av, pthread_mutex_t *fork)
{
	int				i;
	int				*dead;
	int				*full;
	pthread_mutex_t	*lock;

	createphilo(philo, av);
	dead = malloc(sizeof(int));
	*dead = 0;
	full = malloc(sizeof(int));
	*full = 0;
	lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(lock, NULL);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].full = full;
		philo[i].is_ph_dead = dead;
		philo[i].lock = lock;
		philo[i].l_f = &fork[i];
		philo[i].r_f = &fork[(i + 1) % ft_atoi(av[1])];
		i++;
	}
}

pthread_mutex_t	*initmutex(int size)
{
	int				i;
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t) * size);
	i = 0;
	while (i < size)
		pthread_mutex_init(&fork[i++], NULL);
	return (fork);
}
