/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_arg_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nefimov <nefimov@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:38:39 by nefimov           #+#    #+#             */
/*   Updated: 2025/05/21 17:18:14 by nefimov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define RED "\033[31m"
#define WHITE "\033[37m"
#define GRAY_10 "\033[38;5;232m" // 10% gray
#define RESET "\033[0m"

// Check arguments
// Return 0 if OK, 1 if not
int	ph_args_check(int argc, char *argv[], int *args)
{
	if (argc < 5 || argc > 6)
		return (ph_arg_perrmsg("Wrong number of arguments!"));
	if (ph_args_are_int(argc, argv, args))
		return (ph_arg_perrmsg("One or more arguments is not positive int!"));
	return (0);
}

// Print error message and hint for right args
// Return 1;
int	ph_arg_perrmsg(char *errmsg)
{
	printf(RED "%s\n" RESET, errmsg);
	printf("Your program must take the following arguments:\n");
	printf(GRAY_10 "number_of_philosophers time_to_die ");
	printf("time_to_eat time_to_sleep\n");
	printf("[number_of_times_each_philosopher_must_eat]\n" RESET);
	printf("All the numbers should be positive integers.\n");
	return (1);
}

// Check args for only digits.
// Return 0 if OK, 1 if no.
int	ph_args_are_int(int argc, char *argv[], int *args)
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
		args[i - 1] = ph_simple_itoa(argv[i]);
		if (args[i - 1] == -1)
			return (1);
		if (argc == 5)
			args[4] = -1;
	}
	return (0);
}

// Print all arguments
void	ph_args_print(int *args)
{
	int	i;

	printf("\nArgs: ");
	i = -1;
	while (++i < ARGS_NUM)
		printf("%d ", args[i]);
	printf("\n\n");
}
