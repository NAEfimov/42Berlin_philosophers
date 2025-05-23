/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:21:08 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/23 19:55:56 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_threads_allocate(pthread_t **threads, int num)
{
	pthread_t	*thrd;

	thrd = (pthread_t *)malloc((num + 1) * sizeof(pthread_t));
	if (thrd == NULL)
		return (1);
	*threads = thrd;
	return (0);
}

void	ph_threads_stop(t_philo *philo, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		philo[i].is_die = 1;
}

int	ph_threads_create(pthread_t *threads, t_philo *philo, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		pthread_create(&threads[i], NULL, ph_simulation, (void *)&philo[i]);
	pthread_create(&threads[i], NULL, ph_monitor, (void *)philo);
	
	i = -1;
	while (++i < num + 1)
		pthread_join(threads[i], NULL);
	return (0);
}
