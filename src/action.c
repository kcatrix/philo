/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcatrix <kcatrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:04:40 by kevyn             #+#    #+#             */
/*   Updated: 2022/03/25 12:48:28 by kcatrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat(t_philo_i *p)
{
	fork_lock(p);
	ft_usleep(0);
	if (p->pi->death == 0)
	{
		printf("%lld %d has taken fork\n",
			get_time() - p->pi->time, p->i + 1);
		printf("%lld %d is eating\n",
			get_time() - p->pi->time, p->i + 1);
	}
	if (p->pi->death == 0)
		die(p);
	ft_usleep(p->pi->time_to_eat);
	if (p->pi->death == 0)
		die(p);
	p->die += p->pi->time_to_die;
	fork_unlock(p);
	ft_usleep(0);
	return (0);
}

void	dodo(t_philo_i *p)
{
	ft_usleep(0);
	printf("%lld %d is sleeping\n", get_time() - p->pi->time, p->i + 1);
	if (p->pi->death == 0)
		die(p);
	ft_usleep(p->pi->time_to_sleep);
	if (p->pi->death == 0)
		die(p);
	ft_usleep(0);
}

void	die(t_philo_i *p)
{
	ft_usleep(0);
	if (get_time() - p->pi->time > p->die && p->pi->death == 0)
	{
		printf("%lld %d died\n", get_time() - p->pi->time, p->i + 1);
		p->pi->death++;
	}
	ft_usleep(0);
}
