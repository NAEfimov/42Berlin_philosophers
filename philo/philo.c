/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:26 by nefimov           #+#    #+#             */
/*   Updated: 2025/06/03 19:08:35 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int				args[ARGS_COUNT];
	t_mtxs			*mtxs;
	pthread_t		*threads;
	t_philo			*philo;

	mtxs = NULL;
	philo = NULL;
	threads = NULL;
	if (ph_args_check(argc, argv, args)
		|| ph_mtxs_init(&mtxs, args)
		|| ph_philo_create(&philo, mtxs, args)
		|| ph_threads_allocate(&threads, args[ARGS_PH_NUM])
		|| ph_threads_create(threads, philo, args[ARGS_PH_NUM]))
	{
		ph_mtxs_destroy(&mtxs);
		ph_free(threads, philo);
		return (1);
	}
	ph_mtxs_destroy(&mtxs);
	ph_free(threads, philo);
	return (0);
}
