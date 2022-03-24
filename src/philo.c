/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:30:28 by operculesan       #+#    #+#             */
/*   Updated: 2022/03/24 15:51:13 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo(int argc, char *argv[], t_philo *P)
{
	if (parse(argc, argv) != 0)
		return (parse(argc, argv));
	init_struct(argc, argv, P);
	pthread_mutex_init(&P->mutex, NULL);
	while (P->i < P->number_of_philo)
	{
		pthread_create(&P->philo[P->i].th, NULL, &action, &P->philo[P->i]);
		P->i++;
		pthread_detach(P->philo[P->i].th);
	}
	clean(P->philo);
	return (0);
}

void	*action(void *arg)
{
	t_philo_i	*p;
	int			i;

	p = (t_philo_i *)arg;
	i = 0;
	while (p->pi->death == 0
		&& i < p->pi->number_of_times_each_philosopher_must_eat)
	{
		if (p->pi->death == 0)
			eat(p);
		if (p->pi->death == 0)
			dodo(p);
		if (p->pi->death == 0)
			printf("%lld ms %d is thinking\n", get_time() - p->pi->time, p->i + 1);
		i++;
	}
	p->pi->fin++;
	return (0);
}

int eat(t_philo_i *p)
{
	int i; 
	
	i = p->i;
	if (i == p->pi->number_of_philo - 1)
		i = -1;
	i++;
	pthread_mutex_lock(&p->fork);
	pthread_mutex_lock(&p->pi->philo[i].fork);
	if (p->pi->death == 0)
	{
		printf("%lld ms %d has taken fork left\n", get_time() - p->pi->time, p->i + 1);
		printf("%lld ms %d has taken fork to right\n", get_time() - p->pi->time, p->i + 1);
		printf("%lld ms %d is eating\n", get_time() - p->pi->time, p->i + 1);
	}
	if (p->pi->death == 0)
		die(p);
	ft_usleep(p->pi->time_to_eat);
	if (p->pi->death == 0)
		die(p);
	if (p->pi->death == 0)
		printf("%lld ms %d end to eat\n", get_time() - p->pi->time, p->i + 1);
	p->die += p->pi->time_to_die;
	pthread_mutex_unlock(&p->pi->philo[i].fork);
	pthread_mutex_unlock(&p->fork);
	return (0);
}

void	dodo(t_philo_i *p)
{
	printf("%lld ms %d is sleeping\n", get_time() - p->pi->time, p->i + 1);
	if (p->pi->death == 0)
		die(p);
	ft_usleep(p->pi->time_to_sleep);
	if (p->pi->death == 0)
		die(p);
	if (p->pi->death == 0)
		printf("%lld ms %d is to wake up\n", get_time() - p->pi->time, p->i + 1);
}

void	die(t_philo_i *p)
{
	if (get_time() - p->pi->time >= p->die && p->pi->death == 0)
	{
		printf("%lld ms %d died\n", get_time() - p->pi->time, p->i + 1);
		p->pi->death++;
	}
}

void	clean(t_philo_i *p)
{
	printf("hello clean \n");
	int i;

	i = 0;
	while (i < p->pi->number_of_philo)
	{
		pthread_join(p->pi->philo[i++].th, NULL);
	}
	i = 0;
	if (p->pi->fin == p->pi->number_of_philo || p->pi->death > 0)
	{
		while (i < p->pi->number_of_philo)
		{
			pthread_mutex_destroy(&p->pi->philo[i++].fork);
		}
		pthread_mutex_destroy(&p->pi->mutex);
		free(p->pi->philo);
		printf("maxi chibre \n");
	}	
}

void	ft_usleep(long time)
{
	long	reference_time;

	reference_time = get_time();
	while (get_time() - reference_time < time)
	{
		usleep(time * 1000);
	}
}
