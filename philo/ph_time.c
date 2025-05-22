/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:07:33 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/21 21:14:19 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ph_get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec % S_TO_MKS * S_TO_MKS + tv.tv_usec);
}