/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:32:01 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/23 12:19:54 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_mtxs_init(pthread_mutex_t **mtxs, int *args)
{
	int				i;
	pthread_mutex_t	*mtx;

	mtx = (pthread_mutex_t *)malloc(args[ARGS_PH_NUM]
			* sizeof(pthread_mutex_t));
	if (mtx == NULL)
		return (1);
	i = -1;
	while (++i < args[ARGS_PH_NUM])
		pthread_mutex_init(&mtx[i], NULL);
	*mtxs = mtx;
	return (0);
}

int	ph_mtxs_destroy(pthread_mutex_t **mtxs, int *args)
{
	int				i;
	pthread_mutex_t	*mtx;

	if (mtxs == NULL || *mtxs == NULL || args == NULL)
		return (0);
	mtx = *mtxs;
	i = -1;
	while (++i < args[0])
	{
		if (pthread_mutex_destroy(&mtx[i]))
			return (1);
	}
	free(mtx);
	*mtxs = NULL;
	return (0);
}
