/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:26 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/21 20:47:28 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int				args[ARGS_COUNT];
	pthread_mutex_t	*mtxs;
	pthread_t		*threads;
	t_philo			*philo;

	mtxs = NULL;
	philo = NULL;
	threads = NULL;
	if (ph_args_check(argc, argv, args))
		return (1);
	// ph_args_print(args);
	// Create mutexes
	if (ph_mtxs_init(&mtxs, args))
		return (1);
	// Create philosophers
	if (ph_philo_create(&philo, mtxs, args))
	{
		// clean and destroy mtxs
		return (1);
	}
	// ph_philo_print_status(philo);
	// Create threads
	if (ph_threads_allocate(&threads, args[ARGS_PH_NUM]))
	{
		// clean and destroy mtxs
		return (1);
	}
	// Start threads
	ph_threads_create(threads, philo, args[ARGS_PH_NUM]);
	// Stop threads
	// Clear allocations
	ph_mtxs_destroy(&mtxs, args);
	ph_free(threads, philo, mtxs);
	return (0);
}
