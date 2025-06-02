/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:06:11 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/02 18:23:58 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_mon_is_die(t_philo *ph)
{
	int	value;

	pthread_mutex_lock(ph->is_die_mtx);
	value = ph->is_die;
	pthread_mutex_unlock(ph->is_die_mtx);
	return (value);
}

long	ph_mon_t_leat(t_philo *ph)
{
	long	value;

	pthread_mutex_lock(ph->t_leat_mtx);
	value = ph->t_leat;
	pthread_mutex_unlock(ph->t_leat_mtx);
	return (value);
}

int	ph_mon_n_eats(t_philo *ph)
{
	int	value;

	pthread_mutex_lock(ph->n_eats_mtx);
	value = ph->n_eats;
	pthread_mutex_unlock(ph->n_eats_mtx);
	return (value);
}
