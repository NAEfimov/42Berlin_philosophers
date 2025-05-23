/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sim_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:52:26 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/23 19:30:37 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_action_eat(t_philo *ph)
{
	// Take left fork
	pthread_mutex_lock(ph->frk_mtx[0]);
	printf("%ld %d has taken a fork\n", ph_get_msec() - ph->t_start, ph->n);
	// If only one philosopher - wait and die
	if (ph->ph_num == 1)
	{
		usleep(MS_TO_MKS * ph->t_die);
		pthread_mutex_lock(ph->is_die_mtx);
		ph->is_die = 1;
		pthread_mutex_unlock(ph->is_die_mtx);
		pthread_mutex_unlock(ph->frk_mtx[0]);
		return (1);
	}
	// Take right fork
	if (ph_check_die(ph))
	{
		pthread_mutex_unlock(ph->frk_mtx[0]);
		return (1);
	}
	pthread_mutex_lock(ph->frk_mtx[1]);
	// Write new t_leat
	if (ph_check_die(ph))
	{
		pthread_mutex_unlock(ph->frk_mtx[0]);
		pthread_mutex_unlock(ph->frk_mtx[1]);
		return (1);
	}
	pthread_mutex_lock(ph->t_leat_mtx);
	ph->t_leat = ph_get_msec();
	printf("%ld %d has taken a fork\n", ph->t_leat - ph->t_start, ph->n);
	printf("%ld %d is eating\n", ph->t_leat - ph->t_start, ph->n);
	pthread_mutex_unlock(ph->t_leat_mtx);
	// Sleep
	usleep(MS_TO_MKS * ph->t_eat);
	// Unlock forks after sleep
	pthread_mutex_unlock(ph->frk_mtx[0]);
	pthread_mutex_unlock(ph->frk_mtx[1]);
	if (ph_check_die(ph))
		return (1);
	// Decrease number of eats
	if (--ph->n_eats == 0)
		return (1);
	return (0);
}

int	ph_action_sleep(t_philo *ph)
{
	printf("%ld %d is sleeping\n", ph_get_msec() - ph->t_start, ph->n);
	usleep(MS_TO_MKS * ph->t_sleep);
	if (ph_check_die(ph))
		return (1);
	return (0);
}

int	ph_action_wait(t_philo *ph, long time)
{
	if (ph->t_sleep <= ph->t_eat)
	{
		usleep(MS_TO_MKS * (time));
		if (ph_check_die(ph))
			return (1);
	}
	ph->status--;
	return (0);
}

int	ph_action_wait_init(t_philo *ph)
{
	printf("%ld %d is thinking\n", ph_get_msec() - ph->t_start, ph->n);
	// usleep(MS_TO_MKS * (ph->t_eat));
	// if (ph_check_die(ph))
	// 	return (1);
	if (ph->status == ph->ph_num - 1)
	{
		usleep(MS_TO_MKS * (ph->t_eat));
		if (ph_check_die(ph))
			return (1);
	}
	ph->status--;
	return (0);
}
