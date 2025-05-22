/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:07:09 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/22 11:03:12 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_set_start_time(t_philo *philo)
{
	philo->t_start = ph_get_time();
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
			
			if ((ph_get_time() - ph->t_leat + ph->t_eat) / MS_TO_MKS >= ph->t_die)
			{
				ph->is_die = 1;
				usleep (ph->t_die);
				return ;
			}
			
			pthread_mutex_lock(ph->frk[0]);
			printf("%d: lock left fork\n", ph->n);
			pthread_mutex_lock(ph->frk[1]);
			printf("%d: lock right fork\n", ph->n);
			
			printf("%d: eat %ld\n", ph->n, (ph_get_time() - ph->t_leat) / MS_TO_MKS);
			ph->n_eats--;
			ph->t_leat = ph_get_time();

			pthread_mutex_unlock(ph->frk[0]);
			pthread_mutex_unlock(ph->frk[1]);
			
			if (ph_get_time() - ph->t_leat + ph->t_sleep >= ph->t_die)
			{
				ph->is_die = 1;
				usleep (ph->t_die);
				return ;
			}
			printf("%d: sleep\n", ph->n);
			usleep(ph->t_sleep);
			
			if (--ph->status < 0)
				ph->status = ph->ph_num - 1;
		}
		else
		{
			// printf("%d: status %d\n", ph->n, 3);
			t_wait = ph_get_time() - ph->t_leat + ph->t_eat;
			
			if (t_wait < ph->t_die)
				usleep(ph->t_eat);
			else
			{
				ph->is_die = 1;
				usleep (ph->t_die);
				return ;
			}
	
			ph->status--;
		}
	}
	else // Action 2: wait t_eat and eat
	{
		// printf("%d: status %d\n", ph->n, 2);
		t_wait = ph_get_time() - ph->t_leat + ph->t_eat;
		// printf("%d: t_wait %ld | t_die %ld\n", ph->n, t_wait, ph->t_die);
		if (t_wait < ph->t_die)
			usleep(ph->t_eat);
		else
		{
			ph->is_die = 1;
			usleep (ph->t_die);
			return ;
		}
			
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
		printf("%d: died %ld\n", ph->n, (ph_get_time() - ph->t_start) / MS_TO_MKS);
	// ph_philo_print(ph);
	
	return NULL;
}
