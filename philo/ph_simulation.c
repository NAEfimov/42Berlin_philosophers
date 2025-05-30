/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:07:09 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/23 11:59:32 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	else
		if (ph_action_wait(ph, ph->t_eat
				- ph->t_sleep * (ph->status / (ph->ph_num - 1))))
			return ;
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
		if (ph_action_wait_init(ph))
			return ;
}

void	*ph_simulation(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph_set_start_time(ph);
	ph_proc_status_init(ph);
	while (ph->n_eats != 0 && !ph->is_die)
		ph_proc_status(ph);
	if (ph->is_die == 1)
		printf("%ld %d died\n", ph_get_msec() - ph->t_start, ph->n);
	return (NULL);
}
