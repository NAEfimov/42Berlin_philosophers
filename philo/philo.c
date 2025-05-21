/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:26 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/21 16:27:36 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	pthread_t		*thrs;
	pthread_mutex_t	*mtxs;

	if (ph_arg_check(argc, argv))
		return (1);
	// Create mutexes
	// Create philosophers
	// Create threads
	// Start threads
	// Stop threads
	// Clear allocations
	return (0);
}
