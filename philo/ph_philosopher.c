/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:28:45 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/28 16:21:24 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define RED "\033[31m"
#define WHITE "\033[37m"
#define GRAY_10 "\033[38;5;232m"
#define RESET "\033[0m"

int	ph_philo_create(t_philo **philo, t_mtxs *mtxs, int *args)
{
	int		i;
	t_philo	*ph;

	ph = (t_philo *)malloc(args[ARGS_PH_NUM] * sizeof(t_philo));
	if (ph == NULL)
		return (1);
	i = -1;
	while (++i < args[ARGS_PH_NUM])
		ph_philo_init(&ph[i], mtxs, args, i);
	*philo = ph;

	return (0);
}

void	ph_philo_init(t_philo *philo, t_mtxs *mtxs, int *args, int i)
{
	philo->n = i + 1;
	philo->status = i;
	philo->ph_num = args[ARGS_PH_NUM];
	philo->t_die = (long)(args[ARGS_T_DIE]);
	philo->t_eat = (long)(args[ARGS_T_EAT]);
	philo->t_sleep = (long)(args[ARGS_T_SLEEP]);
	philo->n_eats = args[ARGS_N_EATS];
	philo->t_start = 0;
	philo->t_leat = 0;
	philo->is_die = 0;
	philo->frk_mtx[0] = &mtxs->frk_mtx[philo->ph_num - 1
		- ((philo->ph_num - i) % philo->ph_num)];
	if (&mtxs->frk_mtx[i] < philo->frk_mtx[0])
	{
		philo->frk_mtx[1] = philo->frk_mtx[0];
		philo->frk_mtx[0] = &mtxs->frk_mtx[i];
	}
	else
		philo->frk_mtx[1] = &mtxs->frk_mtx[i];
	philo->is_die_mtx = &mtxs->is_die_mtx[i];
	philo->t_leat_mtx = &mtxs->t_leat_mtx[i];
}

void	ph_philo_print(t_philo *philo)
{
	printf(RED"\nphilo:\t%d\n"RESET, philo->n);
	printf("status:\t%d\n", philo->status);
	printf(GRAY_10"n_eats:\t%d\n", philo->n_eats);
	printf("t_strt:\t%ld\n", philo->t_start);
	printf("t_leat:\t%ld\n"RESET, philo->t_leat);
	printf("is_die:\t%d\n", philo->is_die);
	printf("forks:\t\t%p | %p\n", philo->frk_mtx[0], philo->frk_mtx[1]);
}

void	ph_philo_print_all(t_philo *philo)
{
	printf(RED"\nphilo:\t\t%d\n"RESET, philo->n);
	printf("status:\t\t%d\n", philo->status);
	printf("ph number:\t%d\n", philo->ph_num);
	printf("t_die:\t\t%ld\n", philo->t_die);
	printf("t_eat:\t\t%ld\n", philo->t_eat);
	printf("t_sleep:\t%ld\n", philo->t_sleep);
	printf("n_eats:\t\t%d\n", philo->n_eats);
	printf("t_start:\t%ld\n", philo->t_start);
	printf("t_leat:\t\t%ld\n", philo->t_leat);
	printf("is_die:\t\t%d\n", philo->is_die);
	printf("forks:\t\t%p | %p\n", philo->frk_mtx[0], philo->frk_mtx[1]);
}

void	ph_philo_print_status(t_philo *philo)
{
	int	i;

	if (philo == NULL)
		return ;
	i = -1;
	while (++i < philo[0].ph_num)
		ph_philo_print_all(&philo[i]);
}
