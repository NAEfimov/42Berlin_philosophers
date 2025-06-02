/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:32:01 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/02 12:33:45 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Allocate memory for (ph_num + 1) mutexes and init them
// First ph_num mutexes are forks. The last one is for ph.is_die
int	ph_mtxs_init(t_mtxs *mtxs, int *args)
{
	int	i;

	mtxs->n = args[ARGS_PH_NUM];
	mtxs->frks = malloc((mtxs->n) * sizeof(int));
	mtxs->frk_mtx = (pthread_mutex_t *)malloc((mtxs->n)
			* sizeof(pthread_mutex_t));
	mtxs->is_die_mtx = (pthread_mutex_t *)malloc((mtxs->n)
			* sizeof(pthread_mutex_t));
	mtxs->t_leat_mtx = (pthread_mutex_t *)malloc((mtxs->n)
			* sizeof(pthread_mutex_t));
	if (!mtxs->frks || !mtxs->frk_mtx || !mtxs->is_die_mtx || !mtxs->t_leat_mtx)
		return (1);
	i = -1;
	while (++i < mtxs->n)
	{
		mtxs->frks[i] = 0;
		pthread_mutex_init(&(mtxs->frk_mtx[i]), NULL);
		pthread_mutex_init(&(mtxs->is_die_mtx[i]), NULL);
		pthread_mutex_init(&(mtxs->t_leat_mtx[i]), NULL);
	}
	return (0);
}

int	ph_mtxs_destroy(t_mtxs *mtxs, int *args)
{
	int	i;

	if (mtxs == NULL || args == NULL)
		return (0);
	i = -1;
	while (++i < mtxs->n)
	{
		if (pthread_mutex_destroy(&(mtxs->frk_mtx[i]))
			|| pthread_mutex_destroy(&(mtxs->is_die_mtx[i]))
			|| pthread_mutex_destroy(&(mtxs->t_leat_mtx[i])))
			return (1);
	}
	if (mtxs->frks)
		free(mtxs->frks);
	if (mtxs->frk_mtx)
		free(mtxs->frk_mtx);
	if (mtxs->is_die_mtx)
		free(mtxs->is_die_mtx);
	if (mtxs->t_leat_mtx)
		free(mtxs->t_leat_mtx);
	mtxs->n = 0;
	mtxs = NULL;
	return (0);
}
