/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:32:01 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/21 19:30:14 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_mtxs_init(pthread_mutex_t **mtxs, int *args)
{
	int	i;
	pthread_mutex_t *mtx;
	
	// Allocate memorry for an array of mutexes
	mtx = (pthread_mutex_t *)malloc(args[ARGS_PH_NUM] * sizeof(pthread_mutex_t));
	if (mtx == NULL)
		return (1);
	// Initialize mutexes
	i = -1;
	while (++i < args[ARGS_PH_NUM])
		pthread_mutex_init(&mtx[i], NULL);
	*mtxs = mtx;
	return (0);
}

int	ph_mtxs_destroy(pthread_mutex_t **mtxs, int *args)
{
	int	i;
	pthread_mutex_t *mtx;

	mtx = *mtxs;
	i = -1;
	while (++i < args[0])
	{
		if (pthread_mutex_destroy(&mtx[i]))
			return (1);
	}
	free(mtx);
	return (0);
}