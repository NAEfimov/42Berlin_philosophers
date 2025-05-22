/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:07:09 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/22 12:34:25 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_set_start_time(t_philo *philo)
{
	philo->t_start = ph_get_msec();
	philo->t_leat = philo->t_start;
}

void ph_proc_status(t_philo *ph)
{
	long	t_wait;

	if (ph->status % 2 == 0) // Action 1: take forks and eat
	{
		if (ph->status != ph->ph_num - 1)
		{
			// printf("%d: status %d\n", ph->n, 1);
			// t_wait = ph_get_time() - ph->t_leat;
			// Check for dead before eat
			t_wait = ph_get_msec() - ph->t_leat;
			// printf("%d: t_wait %ld | t_die %ld\n", ph->n, t_wait, ph->t_die);

			if (t_wait > ph->t_die)
			{
				ph->is_die = 1;
				// usleep(MS_TO_MKS * ph->t_die);
				return ;
			}
			
			// Eat
			pthread_mutex_lock(ph->frk[0]);
			printf("%d: lock left fork %ld\n", ph->n, ph_get_msec() - ph->t_start);
			pthread_mutex_lock(ph->frk[1]);
			printf("%d: lock right fork %ld\n", ph->n, ph_get_msec() - ph->t_start);
			
			printf("%d: eat %ld\n", ph->n, ph_get_msec() - ph->t_start);
			ph->n_eats--;
			ph->t_leat = ph_get_msec();
			usleep(MS_TO_MKS * ph->t_eat);

			pthread_mutex_unlock(ph->frk[0]);
			pthread_mutex_unlock(ph->frk[1]);
			
			// Check for dead before sleep
			t_wait = ph_get_msec() - ph->t_leat + ph->t_sleep;
			if (t_wait >= ph->t_die)
			{
				ph->is_die = 1;
				usleep(MS_TO_MKS * ph->t_die);
				return ;
			}
			// Sleep
			printf("%d: sleep %ld\n", ph->n, ph_get_msec() - ph->t_start);
			usleep(MS_TO_MKS * ph->t_sleep);
			
			if (--ph->status < 0)
				ph->status = ph->ph_num - 1;
		}
		else
		{
			// printf("%d: status %d\n", ph->n, 3);
			if (ph->t_sleep > ph->t_eat)
				{
					ph->status--;
					return ;
				}
			t_wait = ph_get_msec() - ph->t_leat + ph->t_eat;
			
			if (t_wait <= ph->t_die)
				usleep(MS_TO_MKS * ph->t_eat);
			else
			{
				ph->is_die = 1;
				usleep(MS_TO_MKS * ph->t_die);
				return ;
			}
	
			ph->status--;
		}
	}
	else // Action 2: wait t_eat and eat
	{
		// printf("%d: status %d\n", ph->n, 2);
		if (ph->t_sleep > ph->t_eat)
		{
			ph->status--;
			return ;
		}
		// t_wait = ph_get_msec() - ph->t_leat + ph->t_eat;
		t_wait = ph_get_msec() - ph->t_leat + (ph->t_eat - ph->t_sleep);
		// printf("%d: t_wait %ld | t_die %ld\n", ph->n, t_wait, ph->t_die);
		if (t_wait > ph->t_die)
		{
			ph->is_die = 1;
			usleep(MS_TO_MKS * ph->t_die);
			return ;
		}
		usleep(MS_TO_MKS * (ph->t_eat - ph->t_sleep));
			
		ph->status--;
	}
}

void	*ph_simulation(void *philo)
{
	t_philo *ph;

	ph = (t_philo*)philo;
	// Set t_start and t_leat
	ph_set_start_time(ph);
	// Start loop
	// ph_philo_print(ph);
	while (ph->n_eats > 0 && !ph->is_die)
		ph_proc_status(ph);
	if (ph->is_die == 1)
		printf("%d: died %ld\n", ph->n, (ph_get_msec() - ph->t_start));
	// ph_philo_print(ph);
	
	return NULL;
}
