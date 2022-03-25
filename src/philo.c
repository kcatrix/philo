/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcatrix <kcatrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:30:28 by operculesan       #+#    #+#             */
/*   Updated: 2022/03/25 14:16:02 by kcatrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo(int argc, char *argv[], t_philo *P)
{
	if (parse(argc, argv) != 0)
		return (parse(argc, argv));
	init_struct(argc, argv, P);
	pthread_mutex_init(&P->mutex, NULL);
	if (ft_atoi(argv[1]) > 1)
	{
		while (P->i < P->number_of_philo)
		{
			pthread_create(&P->philo[P->i].th, NULL, &action, &P->philo[P->i]);
			P->i++;
			pthread_detach(P->philo[P->i].th);
		}
		clean(P->philo);
	}
	else
		printf("0 1 is died\n");
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
		ft_usleep(0);
		if (p->pi->death == 0)
			eat(p);
		ft_usleep(0);
		if (p->pi->death == 0)
			dodo(p);
		if (p->pi->death == 0)
			printf("%lld %d is thinking\n",
				get_time() - p->pi->time, p->i + 1);
		ft_usleep(0);
		i++;
	}
	p->pi->fin++;
	return (0);
}

void	clean(t_philo_i *p)
{
	int	i;

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
	}	
}

void	ft_usleep(long time)
{
	long	reference_time;

	reference_time = get_time();
	while (get_time() - reference_time < time)
	{
		usleep(time * 10);
	}
}

void	fork_lock(t_philo_i *p)
{
	int	i;

	i = p->i;
	if (i == p->pi->number_of_philo - 1)
		i = -1;
	i++;
	pthread_mutex_lock(&p->fork);
	pthread_mutex_lock(&p->pi->philo[i].fork);
}
