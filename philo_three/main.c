/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:01:12 by abaur             #+#    #+#             */
/*   Updated: 2021/03/06 16:02:25 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minilibft/minilibft.h"
#include "simulation_builder.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int				g_eatgoal = -1;

#ifdef philo_one

static char		*g_philo_variant = "philo_one";

#elif defined philo_two

static char		*g_philo_variant = "philo_two";

#elif defined philo_three

static char		*g_philo_variant = "philo_three";

#endif

static short	parseint(const char *arg, unsigned int *dst)
{
	if (!isnumber(arg))
	{
		write(STDERR_FILENO, "Not a Number : ", 16);
		write(STDERR_FILENO, arg, ministrlen(arg));
		write(STDERR_FILENO, "\n", 1);
		return (FALSE);
	}
	*dst = miniatoi(arg);
	return (TRUE);
}

/*
** Parses a number in milliseconds, and stores its value in microseconds.
*/

static short	parseusec(const char *arg, useconds_t *dst)
{
	if (!parseint(arg, dst))
		return (FALSE);
	*dst *= 1000;
	return (TRUE);
}

static short	parseargs(int argc, char **argv)
{
	if (argc < 5 || 6 < argc)
	{
		write(STDERR_FILENO, "Invalid number of arguments.\n", 28);
		return (FALSE);
	}
	if (!parseint(argv[1], &g_philocount)
		|| !parseusec(argv[2], &g_ttdie)
		|| !parseusec(argv[3], &g_tteat)
		|| !parseusec(argv[4], &g_ttsleep)
		|| (argc == 6 && !parseint(argv[5], (unsigned int*)&g_eatgoal)))
		return (FALSE);
	if (g_philocount < 2)
	{
		write(STDERR_FILENO, "Not enough philosophers.\n", 26);
		return (FALSE);
	}
	return (TRUE);
}

extern int		main(int argc, char **argv)
{
	t_simbuilder	sim;

	debug(0, "%s\n", g_philo_variant);
	if (!parseargs(argc, argv))
		return (EXIT_FAILURE);
	debug(0, "philo count: %i\nttdie: %i\ntteat: %i\nttsleep: %i\ngoal: %i\n",
		g_philocount, g_ttdie, g_tteat, g_ttsleep, g_eatgoal);
	sim_init(&sim);
	sim_start(&sim);
	throw(-1, "[FATAL] Main unexpectedly returned");
	return (EXIT_FAILURE);
}
