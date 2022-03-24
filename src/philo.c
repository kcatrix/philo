/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevyn <kevyn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:30:28 by operculesan       #+#    #+#             */
/*   Updated: 2022/03/24 11:52:45 by kevyn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



/*
	Mutex évite le programme de s'emmélé avec des execution succésive
	int	philo(int argc, char **argv)
{
    
	int* res;
    srand(time(NULL));
    pthread_t th;
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
        return 1;
    }
    if (pthread_join(th, (void**) &res) != 0) {
        return 2;
    }
    printf("Main res: %p\n", res);
    printf("Result: %d\n", *res);
    free(res);
    return 0;
}

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void* fuel_filling(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("Filled fuel... %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel);
        sleep(1);
    }
}

void* car(void* arg) {
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40) {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}
*/
int philo(int argc, char* argv[], t_philo *P) 
{   
    if (parse(argc, argv) != 0)
        return(parse(argc, argv));
    init_struct(argc, argv, P);
    pthread_mutex_init(&P->mutex, NULL);
    while(P->i < P->number_of_philo)
    { 
        pthread_create(&P->philo[P->i].th, NULL, &action, &P->philo[P->i]);
        P->i++;
		pthread_detach(P->philo[P->i].th);
    }
	clean(P->philo);
    return (0);
}

void *action(void *arg)
{
    t_philo_i     *p;
    
    p = (t_philo_i *)arg;
	int i;

	i = 0;
	while (p->P->death == 0 && i < p->P->number_of_times_each_philosopher_must_eat)
	{
		if (p->P->death == 0)
			eat(p);
		if (p->P->death == 0)
			dodo(p);
		if (p->P->death == 0)
			printf("%lld ms %d is thinking\n", get_time() - p->P->time, p->i + 1);
		i++;
	}
	p->P->fin++;
	return (0);
}

int eat(t_philo_i *p)
{
	int i; 
	
	i = p->i;
	if (i == p->P->number_of_philo - 1)
		i = -1;
	i++;
	pthread_mutex_lock(&p->fork);
	pthread_mutex_lock(&p->P->philo[i].fork);
	if (p->P->death == 0)
	{
		printf("%lld ms %d has taken fork\n", get_time() - p->P->time, p->i);
		printf("%lld ms %d has taken fork to %d\n", get_time() - p->P->time, p->i, i);
		printf("%lld ms %d is eating\n", get_time() - p->P->time, p->i);
	}
	if (p->P->death == 0)
		die(p);
	ft_usleep(p->P->time_to_eat);
	if (p->P->death == 0)
		die(p);
	//printf("philo = %d\n", p->i);
	//printf("philo + 1 = %d\n", i);
	if (p->P->death == 0)
		printf("%lld ms %d end to eat\n", get_time() - p->P->time, p->i);
	p->die += p->P->time_to_die;
	pthread_mutex_unlock(&p->P->philo[i].fork);
	pthread_mutex_unlock(&p->fork);
	return (0);
}

void	dodo(t_philo_i *p)
{
	printf("%lld ms %d is sleeping\n", get_time() - p->P->time, p->i);
	if (p->P->death == 0)
		die(p);
	ft_usleep(p->P->time_to_sleep);
	if (p->P->death == 0)
		die(p);
	if (p->P->death == 0)
		printf("%lld ms %d is to wake up\n", get_time() - p->P->time, p->i);
}

void	die(t_philo_i *p)
{
	if (get_time() - p->P->time >= p->die && p->P->death == 0)
	{
		printf("%lld ms %d died\n", get_time() - p->P->time, p->i);
		p->P->death++;
	}
}

void	clean(t_philo_i *p)
{
	printf("hello clean \n");
	//pthread_mutex_lock(&p->P->mutex);
	int i;

	i = 0;
	while (i < p->P->number_of_philo)
	{
		pthread_join(p->P->philo[i++].th, NULL);
	}
	//pthread_mutex_unlock(&p->P->mutex);
	i = 0;
	if (p->P->fin == p->P->number_of_philo || p->P->death > 0)
	{
		while (i < p->P->number_of_philo)
			pthread_mutex_destroy(&p->P->philo[i++].fork);
		pthread_mutex_destroy(&p->P->mutex);
		free(p->P->philo);
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
