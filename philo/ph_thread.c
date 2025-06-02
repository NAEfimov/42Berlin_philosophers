/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:21:08 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/02 21:32:24 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Allocate memory for all philo threads and monitor
int	ph_threads_allocate(pthread_t **threads, int num)
{
	pthread_t	*thrd;

	thrd = (pthread_t *)malloc((num + 1) * sizeof(pthread_t));
	if (thrd == NULL)
		return (1);
	*threads = thrd;
	return (0);
}

// Set t_start for all philosopher and create threads
// Return 0 if OK and 1 if error
int	ph_threads_create(pthread_t *threads, t_philo *philo, int num)
{
	int	i;

	ph_set_philos_t_start(philo);
	i = -1;
	while (++i < num)
	{
		if (pthread_create(&threads[i], NULL, ph_simulation, (void *)&philo[i]))
			return (1);
	}
	if (pthread_create(&threads[i], NULL, ph_monitor, (void *)philo))
		return (1);
	i = -1;
	while (++i < num + 1)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
	}
	return (0);
}

// Set t_start and t_leat for all philosophers
void	ph_set_philos_t_start(t_philo *ph)
{
	int		i;
	long	time;

	time = ph_get_msec();
	i = -1;
	while (++i < ph->ph_num)
	{
		ph[i].t_start = time;
		ph[i].t_leat = time;
	}
}
