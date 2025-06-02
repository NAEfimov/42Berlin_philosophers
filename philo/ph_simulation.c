/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:07:09 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/02 17:22:29 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_simulation(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph_proc_status_init(ph);
	
	pthread_mutex_lock(ph->is_die_mtx);
	while (ph->is_die == 0)
	{
		pthread_mutex_unlock(ph->is_die_mtx);
		ph_proc_status(ph);
		pthread_mutex_lock(ph->is_die_mtx);
	}
	pthread_mutex_unlock(ph->is_die_mtx);

	return (NULL);
}

void	ph_proc_status(t_philo *ph)
{
	if (ph->status % 2 == 0 && ph->status != ph->ph_num - 1)
	{
		if (ph_check_die(ph) || ph_action_eat(ph) || ph_action_sleep(ph))
			return ;
		printf("%ld %d is thinking\n", ph_get_msec() - ph->t_start, ph->n);
		if (--ph->status < 0)
			ph->status = ph->ph_num - 1;
	}
	else if (ph->status % 2 == 1)
	{
		if (ph_action_wait(ph, ph->t_eat - ph->t_sleep))
			return ;
	}
	else
	{
		if (ph_action_wait(ph, ph->t_eat / 2))
			return ;
	}
}

void	ph_proc_status_init(t_philo *ph)
{
	if ((ph->status % 2 == 0 && ph->status != ph->ph_num - 1)
	|| ph->ph_num == 1)
	{
		if (ph_action_eat(ph) || ph_action_sleep(ph))
			return ;
		printf("%ld %d is thinking\n", ph_get_msec() - ph->t_start, ph->n);
		if (--ph->status < 0)
			ph->status = ph->ph_num - 1;
	}
	else
	{
		if (ph_action_wait_init(ph))
			return ;
	}
}

