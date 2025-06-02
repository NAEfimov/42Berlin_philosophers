/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:40:07 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/02 21:34:34 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Free philo and threads allocated memory
void	ph_free(pthread_t *threads, t_philo *philo)
{
	if (philo)
		free(philo);
	if (threads)
		free(threads);
}
