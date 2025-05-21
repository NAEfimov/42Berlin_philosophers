/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:21:08 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/21 20:38:37 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_threads_allocate(pthread_t **threads, int num)
{
	// int	i;
	pthread_t *thrd;

	thrd = (pthread_t *)malloc(num * sizeof(pthread_t));
	if (thrd == NULL)
		return (1);
	*threads = thrd;
	return (0);
}

int	ph_threads_create(pthread_t *threads, t_philo *philo, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		pthread_create(&threads[i], NULL, simulation, (void*)&philo[i]);

	i = -1;
	while (++i < num)
		pthread_join(threads[i], NULL);
	return (0);
}

void	*simulation(void *philo)
{
	t_philo *ph;

	ph = (t_philo*)philo;
	sleep(ph->n % ph->ph_num);
	ph_philo_print(ph);
	return NULL;
}