/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:42:53 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/02 18:24:18 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_mon_set_all_die(t_philo	*ph)
{
	int	i;

	i = -1;
	while (++i < ph->ph_num)
	{
		pthread_mutex_lock(ph[i].is_die_mtx);
		ph[i].is_die = 1;
		pthread_mutex_unlock(ph[i].is_die_mtx);
	}
	return (1);
}

int	ph_mon_check_die(t_philo *ph)
{
	int		i;
	int		evb_eat;

	usleep(MONITOR_SLEEP);
	i = -1;
	evb_eat = 0;
	while (++i < ph->ph_num)
	{
		if (ph_mon_is_die(&ph[i])
			|| ph_get_msec() - ph_mon_t_leat(&ph[i]) > ph[i].t_die)
		{
			if (ph_mon_n_eats(&ph[i]) != 0)
				printf("%ld %d died\n", ph_get_msec()
					- ph[i].t_start, ph[i].n);
			return (ph_mon_set_all_die(ph));
		}
		evb_eat += ph_mon_n_eats(&ph[i]);
	}
	if (evb_eat == 0)
		return (ph_mon_set_all_die(ph));
	return (0);
}

void	*ph_monitor(void *philo)
{
	while (ph_mon_check_die((t_philo *)philo) == 0)
		;
	return (NULL);
}
