/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:32:01 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/02 20:50:55 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Initialise mtxs fields with NULL and 0
static void	set_null_mtxs(t_mtxs **mtxs)
{
	(*mtxs)->n = 0;
	(*mtxs)->frks = NULL;
	(*mtxs)->frk_mtx = NULL;
	(*mtxs)->is_die_mtx = NULL;
	(*mtxs)->t_leat_mtx = NULL;
	(*mtxs)->n_eats_mtx = NULL;
}

// Allocate memory for forks and mutexes and init them
int	ph_mtxs_init(t_mtxs **mtxs, int *args)
{
	int		i;

	*mtxs = malloc(sizeof(t_mtxs));
	if (*mtxs == NULL)
		return (1);
	set_null_mtxs(mtxs);
	(*mtxs)->n = args[ARGS_PH_NUM];
	(*mtxs)->frks = malloc(((*mtxs)->n) * sizeof(int));
	(*mtxs)->frk_mtx = malloc(((*mtxs)->n) * sizeof(pthread_mutex_t));
	(*mtxs)->is_die_mtx = malloc(((*mtxs)->n) * sizeof(pthread_mutex_t));
	(*mtxs)->t_leat_mtx = malloc(((*mtxs)->n) * sizeof(pthread_mutex_t));
	(*mtxs)->n_eats_mtx = malloc(((*mtxs)->n) * sizeof(pthread_mutex_t));
	if (!(*mtxs)->frks || !(*mtxs)->frk_mtx || !(*mtxs)->is_die_mtx
		|| !(*mtxs)->t_leat_mtx || !(*mtxs)->n_eats_mtx)
		return (1);
	i = -1;
	while (++i < (*mtxs)->n)
	{
		(*mtxs)->frks[i] = 0;
		pthread_mutex_init(&((*mtxs)->frk_mtx[i]), NULL);
		pthread_mutex_init(&((*mtxs)->is_die_mtx[i]), NULL);
		pthread_mutex_init(&((*mtxs)->t_leat_mtx[i]), NULL);
		pthread_mutex_init(&((*mtxs)->n_eats_mtx[i]), NULL);
	}
	return (0);
}

static int	destroy_mutexes(t_mtxs *mtx)
{
	int	i;

	i = -1;
	while (++i < mtx->n)
	{
		if (pthread_mutex_destroy(&(mtx->frk_mtx[i]))
			|| pthread_mutex_destroy(&(mtx->is_die_mtx[i]))
			|| pthread_mutex_destroy(&(mtx->t_leat_mtx[i]))
			|| pthread_mutex_destroy(&(mtx->n_eats_mtx[i])))
			return (1);
	}
	return (0);
}

// Destroy mutexes and free allocated memory for mtxs
int	ph_mtxs_destroy(t_mtxs *mtx)
{
	if (mtx == NULL)
		return (0);
	if (destroy_mutexes(mtx))
		return (1);
	if (mtx->frks)
		free(mtx->frks);
	if (mtx->frk_mtx)
		free(mtx->frk_mtx);
	if (mtx->is_die_mtx)
		free(mtx->is_die_mtx);
	if (mtx->t_leat_mtx)
		free(mtx->t_leat_mtx);
	if (mtx->n_eats_mtx)
		free(mtx->n_eats_mtx);
	mtx->n = 0;
	if (mtx)
		free(mtx);
	mtx = NULL;
	return (0);
}
