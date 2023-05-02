/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguler <eguler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:44:04 by eguler            #+#    #+#             */
/*   Updated: 2022/08/01 12:33:51 by eguler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <time.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	long			timetodie;
	long			timetoeat;
	long			timetosleep;
	long			death;
	long			time_to_start;
	int				id;
	int				nbrphilo;
	int				howmanyeat;
	int				eatcount;
	int				*full;
	struct timeval	tv;
	long			start;
	long			ms;
	int				*is_ph_dead;
	pthread_mutex_t	*l_f;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*mutex;
	pthread_t		thread;
}				t_philo;

pthread_mutex_t	*initmutex(int size);
long			ft_atoi(const char *str);
int				setup(t_philo *data, char **av, int ac);
int				is_digit(char *arr);
void			createphilo(t_philo *philo, char **av);
void			createthread(t_philo *philo, int size);
void			gokill(t_philo *philo);
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);
void			get_time(t_philo *ph);
void			*routine(t_philo *philo);
void			ft_usleep(t_philo *philo, long ms);
void			jointhreads(t_philo *ph);
void			take_fork(t_philo *philo);
void			ft_free(t_philo *philo, pthread_mutex_t *mutex);
void			alloandinit(t_philo *philo, char **av, pthread_mutex_t *fork);

#endif