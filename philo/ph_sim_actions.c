/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sim_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:52:26 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/02 21:57:09 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Eat action
// Return 0 if OK, 1 if philopher is die
int	ph_action_eat(t_philo *ph)
{
	if (ph->ph_num == 1)
		return (ph_sim_only_one_ph(ph));
	if (ph_sim_wait_frks(ph))
		return (1);
	if (ph_sim_eating(ph))
		return (1);
	return (0);
}

// Sleep action
// Return 0 if OK, 1 if philopher is die
int	ph_action_sleep(t_philo *ph)
{
	printf("%ld %d is sleeping\n", ph_get_msec() - ph->t_start, ph->n);
	usleep(MS_TO_MKS * ph->t_sleep);
	if (ph_check_die(ph))
		return (1);
	return (0);
}

// Wait action
// Return 0 if OK, 1 if philopher is die
int	ph_action_wait(t_philo *ph, long time)
{
	if (ph->t_eat >= ph->t_sleep)
	{
		usleep(MS_TO_MKS * (time));
		if (ph_check_die(ph))
			return (1);
	}
	ph->status--;
	return (0);
}

// Initialisation wait action
// Return 0 if OK, 1 if philopher is die
int	ph_action_wait_init(t_philo *ph)
{
	printf("%ld %d is thinking\n", ph_get_msec() - ph->t_start, ph->n);
	if (ph->status % 2 == 1)
		usleep(MS_TO_MKS * (ph->t_eat));
	else
	{
		usleep(MS_TO_MKS * (ph->t_eat) * 2);
		ph->status--;
	}
	if (ph_check_die(ph))
		return (1);
	ph->status--;
	return (0);
}
