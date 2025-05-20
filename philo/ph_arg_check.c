/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_arg_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:38:39 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/20 22:39:30 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Check arguments
// Return 0 if OK, 1 if not
int	arg_check(int argc, char *argv[])
{
	if (argc < 5 || argc > 6 || arg_check_int(argc, argv))
		return (arg_perrmsg());
	if (argv[1])
	return (0);
}

// Print error message and hint for right args
// Return 1;
int	arg_perrmsg(void)
{
	printf("Wrong arguments!\n");
	printf("Your program must take the following arguments:\n");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep\n");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (1);
}

// Check args for only digits.
// Return 0 if OK, 1 if no.
int	arg_check_int(int argc, char *argv[])
{
	int		i;
	char	*str;

	i = 0;
	while (++i < argc)
	{
		str = argv[i];
		while (*str)
		{
			if (*str < '0' || *str > '9')
				return (1);
			str++;
		}
	}
	return (0);
}
