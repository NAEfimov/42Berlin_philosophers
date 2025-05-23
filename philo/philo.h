/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:36 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/23 20:00:30 by nefimov          ###   ########.fr       */
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

# define ARGS_COUNT		5

# define ARGS_PH_NUM	0
# define ARGS_T_DIE		1
# define ARGS_T_EAT		2
# define ARGS_T_SLEEP	3
# define ARGS_N_EATS	4

# define MS_TO_MKS		1000
# define S_TO_MKS		1000000

# define MN_SLEEP		500

typedef struct s_philo
{
	int				n;
	int				status;
	int				ph_num;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				n_eats;
	long			t_start;
	long			t_leat;
	int				is_die;
	pthread_mutex_t	*frk_mtx[2];
	pthread_mutex_t	*is_die_mtx;
	pthread_mutex_t	*t_leat_mtx;
}	t_philo;

typedef struct s_mtxs
{
	int				n;
	pthread_mutex_t	*frk_mtx;
	pthread_mutex_t	*is_die_mtx;
	pthread_mutex_t	*t_leat_mtx;
}	t_mtxs;

// ph_arg_check.c
int		ph_args_check(int argc, char *argv[], int *args);
int		ph_args_are_int(int argc, char *argv[], int *args);
int		ph_arg_perrmsg(char *errmsg);
void	ph_args_print(int *args);

// ph_utils.c
int		ph_simple_itoa(char *str);
void	ph_free(pthread_t *threads, t_philo *philo);

// ph_mutex.c
int		ph_mtxs_init(t_mtxs *mtxs, int *args);
int		ph_mtxs_destroy(t_mtxs *mtxs, int *args);

// ph_philosopher.c
int		ph_philo_create(t_philo **philo, t_mtxs *mtxs, int *args);
void	ph_philo_init(t_philo *philo, t_mtxs *mtxs,
			int *args, int order_num);
void	ph_philo_print(t_philo *philo);
void	ph_philo_print_all(t_philo *philo);
void	ph_philo_print_status(t_philo *philo);

// ph_thread.c
int		ph_threads_allocate(pthread_t **threads, int num);
int		ph_threads_create(pthread_t *threads, t_philo *philo, int num);

// ph_time.c
long	ph_get_msec(void);

// ph_simulation.h
void	*ph_simulation(void *philo);
void	ph_proc_status(t_philo *ph);
void	ph_proc_status_init(t_philo *ph);

// ph_sim_actions.c
int		ph_action_eat(t_philo *ph);
int		ph_action_sleep(t_philo *ph);
int		ph_action_wait(t_philo *ph, long time);
int		ph_action_wait_init(t_philo *ph);

// ph_sim_checks.c
void	ph_set_start_time(t_philo *ph);
int		ph_check_die(t_philo *ph);
int		ph_check_t_sleep(t_philo *ph);
int		ph_check_wait_time(t_philo *ph, long time);

// ph_monitor.c
void	*ph_monitor(void *philo);
int		ph_mon_set_all_die(t_philo	*ph);

#endif