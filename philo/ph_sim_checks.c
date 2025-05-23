/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sim_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:52:40 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/23 11:59:38 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_set_start_time(t_philo *ph)
{
	ph->t_start = ph_get_msec();
	ph->t_leat = ph->t_start;
}

int	ph_check_die(t_philo *ph)
{
	if (ph_get_msec() - ph->t_leat > ph->t_die)
	{
		ph->is_die = 1;
		return (1);
	}
	return (0);
}

int	ph_check_t_sleep(t_philo *ph)
{
	if (ph->t_eat + ph->t_sleep > ph->t_die)
	{
		ph->is_die = 1;
		return (1);
	}
	return (0);
}

int	ph_check_wait_time(t_philo *ph, long time)
{
	if (ph_get_msec() - ph->t_leat + time > ph->t_die)
	{
		ph->is_die = 1;
		return (1);
	}
	return (0);
}
