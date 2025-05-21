/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:26 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/21 17:17:27 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int				args[ARGS_NUM];
	pthread_t		*thrs;
	pthread_mutex_t	*mtxs;

	if (ph_args_check(argc, argv, args))
		return (1);
	// Create mutexes
	if (ph_mtxs_init(&mtxs, args))
		return (1);
	// Create philosophers
	// Create threads
	// Start threads
	// Stop threads
	// Clear allocations
	ph_mtxs_destroy(&mtxs, args);
	return (0);
}
