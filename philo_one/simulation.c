/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:57:37 by abaur             #+#    #+#             */
/*   Updated: 2021/02/13 15:08:39 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "simulation.h"

#include "chronos.h"
#include "philosopher.h"
#include "sustenance_ustensile.h"
#include "minilibft/minilibft.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
** Kills all philosophers and wait for them to die out.
** @param int count	The amount of philosophers to kill.
*/

static void		simulation_abort(int count)
{
	int	i;

	g_sim_status = sim_stopped;
	dprintf(STDERR_FILENO, "%5i Simulation stopped\n", stopwatch_date() / 1000);
	i = -1;
	while (++i < count)
	{
		g_hoomans[i].status = phi_dead;
		if (g_hoomans[i].thread != (pthread_t){ 0 })
		{
			pthread_join(g_hoomans[i].thread, NULL);
			g_hoomans[i].thread = (pthread_t){ 0 };
		}
	}
}

static short	simulation_init(void)
{
	unsigned int	i;
	signed int		status;

	g_sim_status = sim_playing;
	i = -1;
	while (++i < g_philocount)
	{
		status = pthread_create(&g_hoomans[i].thread, NULL,
			(void*(*)(void*))&philo_main, &g_hoomans[i]);
		if (status < 0)
		{
			simulation_abort(i);
			return (FALSE);
		}
	}
	return (TRUE);
}

extern short	simulation_main(void)
{
	stopwatch_start();
	if (!simulation_init())
	{
		write(STDERR_FILENO, "Thread initialisation failed.\n", 31);
		return (EXIT_FAILURE);
	}
	wait_until(g_ttdie);
	simulation_abort(g_philocount);
	return (EXIT_SUCCESS);
}
