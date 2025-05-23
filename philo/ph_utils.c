/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:40:07 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/23 12:15:33 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_simple_itoa(char *str)
{
	long	num;

	num = 0;
	while (*str)
	{
		if (num > INT_MAX / 10)
			return (-1);
		num = num * 10 + (*str - '0');
		str++;
	}
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}

void	ph_free(pthread_t *threads, t_philo *philo, pthread_mutex_t *mtxs)
{
	if (philo)
		free(philo);
	if (mtxs)
		free(mtxs);
	if (threads)
		free(threads);
}
