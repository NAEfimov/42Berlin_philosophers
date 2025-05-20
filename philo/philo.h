/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:32:36 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/20 22:40:51 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

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
int	arg_perrmsg(void);

// ph_utils.c

#endif