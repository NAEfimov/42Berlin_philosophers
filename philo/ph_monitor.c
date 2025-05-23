/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:42:53 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/23 20:08:20 by nefimov          ###   ########.fr       */
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
	return(0);
}

void	*ph_monitor(void *philo)
{
	t_philo	*ph;
	int		i;
	int		die;

	die = 0;
	ph = (t_philo *)philo;
	while (die == 0)
	{
		usleep(MN_SLEEP);
		i = -1;
		while (++i < ph->ph_num)
		{
			pthread_mutex_lock(ph[i].t_leat_mtx);
			pthread_mutex_lock(ph[i].is_die_mtx);	
			if (ph[i].is_die || ph_get_msec() - ph[i].t_leat > ph[i].t_die)
			{
				if (ph[i].n_eats != 0)
					printf("%ld %d died\n", ph_get_msec() - ph[i].t_start, ph[i].n);
				pthread_mutex_unlock(ph[i].is_die_mtx);			
				pthread_mutex_unlock(ph[i].t_leat_mtx);
				ph_mon_set_all_die(ph);
				die = 1;
				break ;
			}
			pthread_mutex_unlock(ph[i].is_die_mtx);			
			pthread_mutex_unlock(ph[i].t_leat_mtx);
		}
	}
	return (NULL);
}