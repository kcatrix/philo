/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:13:54 by operculesan       #+#    #+#             */
/*   Updated: 2022/03/24 15:49:30 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parse(int argc, char **argv)
{
	int	i;
	int	y;

	i = 1;
	if (argc != 5 && argc != 6)
		return (1);
	while (argv[i])
	{
		while (argv[i][y])
		{
			if (ft_isdigit(argv[i][y]) == 1)
				return (2);
			y++;
		}
		y = 0;
		i++;
	}
	i = 0;
	while (argv[i])
	{
		if (ft_atoi(argv[i++]) > 1000)
			return (3);
	}
	return (0);
}

void	init_struct(int argc, char **argv, t_philo *P)
{
	long long	time;
	int			i;

	i = 0;
	time = get_time();
	P->time = time;
	P->i = 0;
	P->fin = 0;
	P->death = 0;
	P->number_of_philo = ft_atoi(argv[1]);
	P->philo = malloc(sizeof(t_philo_i) * P->number_of_philo);
	P->time_to_die = ft_atoi(argv[2]);
	while (i != P->number_of_philo)
	{
		P->philo[i].th = malloc(sizeof(pthread_t));
		P->philo[i].i = i;
		P->philo[i].pi = P;
		P->philo[i].die = P->time_to_die;
		pthread_mutex_init(&P->philo[i].fork, NULL);
		P->philo[i++].action = 0;
	}
	P->time_to_eat = ft_atoi(argv[3]);
	P->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		P->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		P->number_of_times_each_philosopher_must_eat = 99999999;
}

long	get_time(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}