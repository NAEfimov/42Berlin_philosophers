/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:07:09 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/22 18:51:24 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_set_start_time(t_philo *philo)
{
	philo->t_start = ph_get_msec();
	philo->t_leat = philo->t_start;
}

int	ph_check_die(t_philo *ph)
{
	// printf("%d: t_wait %ld | t_die %ld\n", ph->n, ph_get_msec() - ph->t_leat, ph->t_die);
	if (ph_get_msec() - ph->t_leat > ph->t_die)
	{	
		ph->is_die = 1;
		return (1);
	}
	return (0);
}
int ph_check_t_sleep(t_philo *ph)
{
	if (ph->t_eat + ph->t_sleep > ph->t_die)
	{	
		ph->is_die = 1;
		return (1);
	}
	return (0);
}

int ph_check_wait_time(t_philo *ph, long time)
{
	// printf("%ld %d checking time %ld | %ld\n", ph_get_msec() - ph->t_start, ph->n, ph_get_msec() - ph->t_leat + time, ph->t_die);
	if (ph_get_msec() - ph->t_leat + time > ph->t_die)
	{	
		ph->is_die = 1;
		return (1);
	}
	return (0);
}

void	ph_action_eat(t_philo *ph)
{
	pthread_mutex_lock(ph->frk[0]);
	printf("%ld %d has taken a fork\n", ph_get_msec() - ph->t_start, ph->n);
	if (ph->ph_num == 1)
	{
		usleep(MS_TO_MKS * ph->t_die);
		ph->is_die = 1;
		return ;
	}
	pthread_mutex_lock(ph->frk[1]);
	ph->t_leat = ph_get_msec();
	printf("%ld %d has taken a fork\n", ph->t_leat - ph->t_start, ph->n);
	printf("%ld %d is eating\n", ph->t_leat - ph->t_start, ph->n);
	ph->n_eats--;
	if (ph_check_wait_time(ph, ph->t_eat))
		{
			usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
			return ;
		}
	usleep(MS_TO_MKS * ph->t_eat);

	pthread_mutex_unlock(ph->frk[0]);
	pthread_mutex_unlock(ph->frk[1]);
}

void	ph_action_sleep(t_philo *ph)
{
	printf("%ld %d is sleeping\n", ph->t_leat - ph->t_start + ph->t_eat, ph->n);
	usleep(MS_TO_MKS * ph->t_sleep);
}

void ph_proc_status(t_philo *ph)
{
	// long	t_wait;

	if (ph->status % 2 == 0) // Action 1: take forks and eat
	{
		if (ph->status != ph->ph_num - 1)
		{
			if (ph_check_die(ph))
				return ;
			
			ph_action_eat(ph);
			if (ph->n_eats == 0 || ph->is_die == 1)
				return ;
			
			if (ph_check_t_sleep(ph))
			{
				usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
				return ;
			}
			ph_action_sleep(ph);
			printf("%ld %d is thinking\n", ph_get_msec() - ph->t_start, ph->n);
			
			if (--ph->status < 0)
				ph->status = ph->ph_num - 1;
		}
		else // Action 3
		{
			if (ph->t_sleep >= ph->t_eat)
				{
					ph->status--;
					return ;
				}

			if (ph_check_wait_time(ph, ph->t_eat - ph->t_sleep))
			{
				usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
				return ;
			}
			usleep(MS_TO_MKS * (ph->t_eat - ph->t_sleep));
			ph->status--;
		}
	}
	else // Action 2: wait t_eat and eat
	{
		if (ph->t_sleep >= ph->t_eat)
		{
			ph->status--;
			return ;
		}
		if (ph_check_wait_time(ph, ph->t_eat))
		{
			usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
			return ;
		}
		usleep(MS_TO_MKS * (ph->t_eat));
			
		ph->status--;
	}
}

void ph_proc_init(t_philo *ph)
{
	// long	t_wait;

	if (ph->status % 2 == 0) // Action 1: take forks and eat
	{
		if (ph->status != ph->ph_num - 1 || ph->ph_num == 1)
		{
			ph_action_eat(ph);
			if (ph->n_eats == 0 || ph->is_die == 1)
				return ;
			
			if (ph_check_t_sleep(ph))
			{
				usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
				return ;
			}
			ph_action_sleep(ph);
			printf("%ld %d is thinking\n", ph_get_msec() - ph->t_start, ph->n);
			
			if (--ph->status < 0)
				ph->status = ph->ph_num - 1;
		}
		else
		{
			printf("%ld %d is thinking\n", ph_get_msec() - ph->t_start, ph->n);
			
			if (ph_check_wait_time(ph, ph->t_eat))
			{
				usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
				return ;
			}
			usleep(MS_TO_MKS * (ph->t_eat));
			ph->status--;
		}
	}
	else // Action 2: wait t_eat and eat
	{
		printf("%ld %d is thinking\n", ph_get_msec() - ph->t_start, ph->n);
		if (ph_check_wait_time(ph, ph->t_eat))
			{
				usleep(MS_TO_MKS * (ph->t_die - ph_get_msec() + ph->t_leat));
				return ;
			}
		usleep(MS_TO_MKS * ph->t_eat);
			
		ph->status--;
	}
}

void	*ph_simulation(void *philo)
{
	t_philo *ph;

	ph = (t_philo*)philo;
	ph_set_start_time(ph);
	ph_proc_init(ph);
	while (ph->n_eats != 0 && !ph->is_die)
		ph_proc_status(ph);
	if (ph->is_die == 1)
		printf("%ld %d died\n", ph_get_msec() - ph->t_start, ph->n);
	// ph_philo_print(ph);
	
	return NULL;
}
