/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:07:09 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/22 09:07:41 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*ph_simulation(void *philo)
{
	t_philo *ph;

	ph = (t_philo*)philo;
	sleep(ph->n % ph->ph_num);
	ph_philo_print(ph);
	return NULL;
}
