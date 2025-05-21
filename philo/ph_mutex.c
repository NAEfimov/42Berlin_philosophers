/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:32:01 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/21 17:00:57 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_mtxs_init(pthread_mutex_t **mtxs, int *args)
{
	int	i;
	
	// Allocate memorry for an array of mutexes
	*mtxs = (pthread_mutex_t*)malloc(args[0] * sizeof(pthread_mutex_t));
	if (*mtxs == NULL)
		return (1);
	// Initialize mutexes
	i = -1;
	while (++i < args[0])
		pthread_mutex_init(mtxs[i], NULL);
	
	return (0);
}

int	ph_mtxs_destroy(pthread_mutex_t **mtxs, int *args)
{
	int	i;

	i = -1;
	while (++i < args[0])
	{
		if (pthread_mutex_destroy(mtxs[i]))
			return (1);
	}
	free(*mtxs);
	return (0);
}