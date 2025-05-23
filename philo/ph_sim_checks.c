/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sim_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:52:40 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/23 19:01:58 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_set_start_time(t_philo *ph)
{
	ph->t_start = ph_get_msec();
	pthread_mutex_lock(ph->t_leat_mtx);
	ph->t_leat = ph->t_start;
	pthread_mutex_unlock(ph->t_leat_mtx);
	// printf("%d set_start_time\n", ph->n);
}

int	ph_check_die(t_philo *ph)
{
	pthread_mutex_lock(ph->is_die_mtx);
	if (ph->is_die)
	{
		pthread_mutex_unlock(ph->is_die_mtx);
		return (1);
	}
	pthread_mutex_unlock(ph->is_die_mtx);
	return (0);
}

int	ph_check_t_sleep(t_philo *ph)
{
	pthread_mutex_lock(ph->is_die_mtx);
	if (ph->t_eat + ph->t_sleep > ph->t_die)
	{
		ph->is_die = 1;
		pthread_mutex_unlock(ph->is_die_mtx);
		return (1);
	}
	return (0);
}

int	ph_check_wait_time(t_philo *ph, long time)
{
	pthread_mutex_lock(ph->is_die_mtx);
	if (ph_get_msec() - ph->t_leat + time > ph->t_die)
	{
		ph->is_die = 1;
		pthread_mutex_unlock(ph->is_die_mtx);
		return (1);
	}
	return (0);
}
