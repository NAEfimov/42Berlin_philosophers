/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sim_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:52:40 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/02 21:53:49 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Check if the philosopher is die
int	ph_check_die(t_philo *ph)
{
	if (ph_mon_is_die(ph))
		return (1);
	return (0);
}
