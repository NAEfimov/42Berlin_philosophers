/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:07:09 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/02 21:43:39 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Thread function for philosophers
void	*ph_simulation(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph_proc_status_init(ph);
	while (ph_mon_is_die(ph) == 0)
		ph_proc_status(ph);
	return (NULL);
}

// Process curent status of philosophers
// If status is even - eat, sleep and change status
// If status is odd - wait and change status
// If status is equal to ph_num - 1 - extra sleep
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

// Initial process for philosophers
void	ph_proc_status_init(t_philo *ph)
{
	if ((ph->status % 2 == 0 && ph->status != ph->ph_num - 1)
		|| (ph->ph_num == 1))
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
