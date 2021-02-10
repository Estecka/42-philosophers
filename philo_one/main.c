/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:01:12 by abaur             #+#    #+#             */
/*   Updated: 2021/02/10 17:17:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "philosopher.h"
#include "simulation.h"
#include "sustenance_ustensile.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int				g_eatgoal = -1;

extern size_t	ministrlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

static int		miniatoi(const char *arg)
{
	int result;

	result = 0;
	while (*arg)
	{
		result = (result * 10) + *arg - '0';
		arg++;
	}
	return (result);
}

static short	isnumber(const char *arg)
{
	while (*arg)
	{
		if (*arg < '0' || '9' < *arg)
			return (FALSE);
		arg++;
	}
	return (TRUE);
}

static short	parseint(const char *arg, int *dst)
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

extern int		main(int argc, char **argv)
{
	int	status;

	if (argc < 5 || 6 < argc)
	{
		write(STDERR_FILENO, "Invalid number of argument\n", 28);
		return (EXIT_FAILURE);
	}
	if (!parseint(argv[1], &g_philocount)
		|| !parseint(argv[2], &g_ttdie)
		|| !parseint(argv[3], &g_tteat)
		|| !parseint(argv[4], &g_ttsleep)
		|| (argc == 6 && !parseint(argv[5], &g_eatgoal))
		|| !ustensile_init(g_philocount))
		return (EXIT_FAILURE);
	if (!philo_init(g_philocount))
	{
		ustensile_deinit();
		return (EXIT_FAILURE);
	}
	printf("philo count: %i\nttdie: %i\ntteat: %i\nttsleep: %i\ngoal: %i\n",
		g_philocount, g_ttdie, g_tteat, g_ttsleep, g_eatgoal);
	status = simulation_main();
	philo_deinit();
	ustensile_deinit();
	return (status);
}
