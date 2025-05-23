/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sim_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:52:26 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/23 13:16:42 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_action_eat(t_philo *ph)
{
	pthread_mutex_lock(ph->frk[0]);
	if (ph_check_die(ph))
	{
		pthread_mutex_unlock(ph->frk[0]);
		return (1);
	}
	printf("%ld %d has taken a fork\n", ph_get_msec() - ph->t_start, ph->n);
	if (ph->ph_num == 1)
	{
		usleep(MS_TO_MKS * ph->t_die);
		ph->is_die = 1;
		return (1);
	}
	pthread_mutex_lock(ph->frk[1]);
	if (ph_check_die(ph))
	{
		pthread_mutex_unlock(ph->frk[0]);
		pthread_mutex_unlock(ph->frk[1]);
		return (1);
	}
	ph->t_leat = ph_get_msec();
	printf("%ld %d has taken a fork\n", ph->t_leat - ph->t_start, ph->n);
	printf("%ld %d is eating\n", ph->t_leat - ph->t_start, ph->n);
	if (ph_check_wait_time(ph, ph->t_eat))
	{
		usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
		return (1);
	}
	usleep(MS_TO_MKS * ph->t_eat);
	pthread_mutex_unlock(ph->frk[0]);
	pthread_mutex_unlock(ph->frk[1]);
	if (--ph->n_eats == 0)
		return (1);
	return (0);
}

int	ph_action_sleep(t_philo *ph)
{
	if (ph_check_t_sleep(ph))
	{
		usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
		return (1);
	}
	printf("%ld %d is sleeping\n", ph->t_leat - ph->t_start + ph->t_eat, ph->n);
	usleep(MS_TO_MKS * ph->t_sleep);
	return (0);
}

int	ph_action_wait(t_philo *ph, long time)
{
	if (ph->t_sleep < ph->t_eat)
	{
		if (ph_check_wait_time(ph, time))
		{
			usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
			return (1);
		}
		usleep(MS_TO_MKS * (time));
	}
	ph->status--;
	return (0);
}

int	ph_action_wait_init(t_philo *ph)
{
	printf("%ld %d is thinking\n", ph_get_msec() - ph->t_start, ph->n);
	if (ph_check_wait_time(ph, ph->t_eat))
	{
		usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
		return (1);
	}
	usleep(MS_TO_MKS * (ph->t_eat));
	ph->status--;
	return (0);
}
