/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:36 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/21 17:18:14 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define ARGS_NUM	5

typedef struct s_philo
{
	int				n;
	int				int_n;
	int				t_num;
	int				fork[2];
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				lst_eat;
	int				eat_n;
	int				is_die;
	pthread_mutex_t	mtx[2];
}	t_philo;

// ph_arg_check.c
int		ph_args_check(int argc, char *argv[], int *args);
int		ph_args_are_int(int argc, char *argv[], int *args);
int		ph_arg_perrmsg(char *errmsg);
void	ph_args_print(int *args);

// ph_utils.c
int	ph_simple_itoa(char *str);

// ph_mutex.c
int	ph_mtxs_init(pthread_mutex_t **mtxs, int *args);
int	ph_mtxs_destroy(pthread_mutex_t **mtxs, int *args);

#endif