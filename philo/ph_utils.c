/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:40:07 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/03 19:15:51 by nefimov          ###   ########.fr       */
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

static size_t	ph_char_count(long num)
{
	size_t	i;

	if (num == 0)
		return (1);
	i = 0;
	while (num != 0)
	{
		i++;
		num = num / 10;
	}
	return (i);
}

static size_t	ph_ltoa(long num, char *str, size_t pos)
{
	size_t	l;
	size_t	i;

	l = ph_char_count(num);
	i = pos + l;
	while (i-- > pos)
	{
		str[i] = (num % 10) + '0';
		num = num / 10;
	}
	return (l);
}

int	ph_printf(t_philo *ph, char *msg)
{
	size_t	len;
	long	time;
	char	str[STR_MAXLEN];

	time = ph_get_msec() - ph->t_start;
	len = 0;
	len = ph_ltoa(time, str, len);
	str[len++] = ' ';
	len += ph_ltoa((long)ph->n, str, len);
	str[len++] = ' ';
	while (*msg)
	{
		str[len++] = *msg;
		msg++;
	}
	str[len] = '\0';
	write(STDOUT_FILENO, str, len);
	return ((int)len);
}
