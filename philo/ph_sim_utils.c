/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sim_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:29:36 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/03 18:53:23 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Set values of frks to value
void	ph_sim_set_frks(t_philo *ph, int value)
{
	if (ph->ph_num == 1)
	{
		pthread_mutex_lock(ph->frk_mtx[0]);
		*(ph->frks[0]) = value;
		pthread_mutex_unlock(ph->frk_mtx[0]);
	}
	else
	{
		pthread_mutex_lock(ph->frk_mtx[0]);
		pthread_mutex_lock(ph->frk_mtx[1]);
		*(ph->frks[0]) = value;
		*(ph->frks[1]) = value;
		pthread_mutex_unlock(ph->frk_mtx[0]);
		pthread_mutex_unlock(ph->frk_mtx[1]);
	}
}

// Wait while forks are both awailable than take them
// Return 0 if OK, 1 if philopher is die
int	ph_sim_wait_frks(t_philo *ph)
{
	pthread_mutex_lock(ph->frk_mtx[0]);
	pthread_mutex_lock(ph->frk_mtx[1]);
	while (*(ph->frks[0]) || *(ph->frks[1]))
	{
		pthread_mutex_unlock(ph->frk_mtx[0]);
		pthread_mutex_unlock(ph->frk_mtx[1]);
		usleep(THINK_SLEEP);
		if (ph_check_die(ph))
			return (1);
		pthread_mutex_lock(ph->frk_mtx[0]);
		pthread_mutex_lock(ph->frk_mtx[1]);
	}
	*(ph->frks[0]) = 1;
	*(ph->frks[1]) = 1;
	pthread_mutex_unlock(ph->frk_mtx[0]);
	pthread_mutex_unlock(ph->frk_mtx[1]);
	if (ph_check_die(ph))
		return (1);
	ph_printf(ph, "has taken a fork\n");
	ph_printf(ph, "has taken a fork\n");
	return (0);
}

// Update ph->t_leat time and wait for ph->t_eat
// Return 0 if OK, 1 if philopher is die
int	ph_sim_eating(t_philo *ph)
{
	pthread_mutex_lock(ph->t_leat_mtx);
	ph->t_leat = ph_get_msec();
	pthread_mutex_unlock(ph->t_leat_mtx);
	ph_printf(ph, "is eating\n");
	usleep(MS_TO_MKS * ph->t_eat);
	ph_sim_set_frks(ph, 0);
	if (ph_check_die(ph))
		return (1);
	ph_sim_decrease_n_eats(ph);
	return (0);
}

// Decrease ph->n_eats value if it is more than 0
void	ph_sim_decrease_n_eats(t_philo *ph)
{
	pthread_mutex_lock(ph->n_eats_mtx);
	if (ph->n_eats > 0)
		ph->n_eats--;
	pthread_mutex_unlock(ph->n_eats_mtx);
}

// Simulation in case of only one philosopher
int	ph_sim_only_one_ph(t_philo *ph)
{
	ph_sim_set_frks(ph, 1);
	ph_printf(ph, "has taken a fork\n");
	usleep(MS_TO_MKS * ph->t_die);
	pthread_mutex_lock(ph->is_die_mtx);
	ph->is_die = 1;
	pthread_mutex_unlock(ph->is_die_mtx);
	return (1);
}
