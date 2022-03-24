/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:04:40 by kevyn             #+#    #+#             */
/*   Updated: 2022/03/24 16:38:32 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat(t_philo_i *p)
{
	fork_lock(p);
	ft_usleep(0);
	if (p->pi->death == 0)
	{
		printf("%lld ms %d has taken fork left\n",
			get_time() - p->pi->time, p->i + 1);
		printf("%lld ms %d has taken fork to right\n",
			get_time() - p->pi->time, p->i + 1);
		printf("%lld ms %d is eating\n",
			get_time() - p->pi->time, p->i + 1);
	}
	if (p->pi->death == 0)
		die(p);
	ft_usleep(p->pi->time_to_eat);
	if (p->pi->death == 0)
		die(p);
	if (p->pi->death == 0)
		printf("%lld ms %d end to eat\n", get_time() - p->pi->time, p->i + 1);
	p->die += p->pi->time_to_die;
	fork_unlock(p);
	ft_usleep(0);
	return (0);
}

void	dodo(t_philo_i *p)
{
	ft_usleep(0);
	printf("%lld ms %d is sleeping\n", get_time() - p->pi->time, p->i + 1);
	if (p->pi->death == 0)
		die(p);
	ft_usleep(p->pi->time_to_sleep);
	if (p->pi->death == 0)
		die(p);
	if (p->pi->death == 0)
		printf("%lld ms %d is to wake up\n", get_time() - p->pi->time, p->i + 1);
	ft_usleep(0);
}

void	die(t_philo_i *p)
{
	ft_usleep(0);
	if (get_time() - p->pi->time > p->die && p->pi->death == 0)
	{
		printf("%lld ms %d died\n", get_time() - p->pi->time, p->i + 1);
		p->pi->death++;
	}
	ft_usleep(0);
}
