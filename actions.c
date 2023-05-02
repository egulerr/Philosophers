/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguler <eguler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:37:25 by eguler            #+#    #+#             */
/*   Updated: 2022/08/01 12:36:47 by eguler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	if (philo->nbrphilo == 1)
	{
		get_time(philo);
		printf("%ld %d has taken a fork\n", philo->time_to_start, philo->id);
		ft_usleep(philo, philo->timetodie);
		gokill(philo);
		return (NULL);
	}
	while (1)
	{
		take_fork(philo);
		eating(philo);
		if (philo->eatcount == philo->howmanyeat)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	pthread_mutex_lock(philo->lock);
	*philo->full += 1;
	if (*philo->full == philo->nbrphilo)
		*philo->is_ph_dead = 1;
	pthread_mutex_unlock(philo->lock);
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	get_time(philo);
	pthread_mutex_lock(philo->l_f);
	pthread_mutex_lock(philo->r_f);
	get_time(philo);
	printf("\033[0;33m%ld %d has taken a fork left [%p]\n", \
	philo->time_to_start, philo->id, philo->l_f);
	printf("\033[0;33m%ld %d has taken a fork right [%p]\n", \
	philo->time_to_start, philo->id, philo->r_f);
}

void	eating(t_philo *philo)
{
	get_time(philo);
	printf("\033[0;35m%ld %d is a eating\n", philo->time_to_start, philo->id);
	philo->eatcount++;
	ft_usleep(philo, philo->timetoeat);
	philo->death = philo->time_to_start + philo->timetodie;
	pthread_mutex_unlock(philo->l_f);
	pthread_mutex_unlock(philo->r_f);
}

void	sleeping(t_philo *philo)
{
	get_time(philo);
	printf("\033[0;31m%ld %d is sleeping\n", philo->time_to_start, philo->id);
	ft_usleep(philo, philo->timetosleep);
}

void	thinking(t_philo *philo)
{
	get_time(philo);
	printf("\033[0;36m%ld %d is thinking\n", philo->time_to_start, philo->id);
}
