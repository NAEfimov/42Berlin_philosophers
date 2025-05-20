/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:36 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/20 22:57:35 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	int		n;
	int		int_n;
	int		t_num;
	int		fork[2];
	long	t_eat;
	long	t_sleep;
	long	t_die;
	long	lst_eat;
	int		is_die;
	int		eat_n;
}	t_philo;

// ph_arg_check.c
int	arg_check(int argc, char *argv[]);
int	arg_check_int(int argc, char *argv[]);
int	arg_perrmsg(char *errmsg);

// ph_utils.c
int	ph_simple_itoa(char *str);

#endif