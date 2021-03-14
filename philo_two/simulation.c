/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:57:37 by abaur             #+#    #+#             */
/*   Updated: 2021/03/14 19:33:43 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "simulation.h"

#include "chronos.h"
#include "philosopher.h"
#include "sustenance_ustensile.h"
#include "thanatos.h"
#include "minilibft/minilibft.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern void		simulation_emergency_brakes(void)
{
	g_sim_status = sim_stopped;
	stopwatch_stop();
	debug(0, "%5li Simulation stopped\n", (long)stopwatch_date() / 1000);
}

/*
** Kills all philosophers and wait for them to die out.
*/

static void		simulation_abort(void)
{
	unsigned int	i;

	g_sim_status = sim_stopped;
	i = -1;
	while (++i < g_philocount)
	{
		if (g_hoomans->status != phi_dead)
		{
			g_hoomans[i].status = phi_dead;
			pthread_join(g_hoomans[i].thread, NULL);
			g_hoomans[i].thread = (pthread_t){ 0 };
		}
	}
}

static short	simulation_init_one(int i)
{
	signed int	status;

	g_hoomans[i].status = phi_sleeping;
	status = pthread_create(&g_hoomans[i].thread, NULL,
		(void*(*)(void*))&philo_main, &g_hoomans[i]);
	if (status < 0)
	{
		g_hoomans[i].status = phi_dead;
		simulation_abort();
		return (FALSE);
	}
	return (TRUE);
}

static short	simulation_init(void)
{
	unsigned int	i;

	g_sim_status = sim_playing;
	i = -1;
	while ((i += 2) < g_philocount)
		if (!simulation_init_one(i))
			return (FALSE);
	i = -2;
	while ((i += 2) < g_philocount)
		if (!simulation_init_one(i))
			return (FALSE);
	return (TRUE);
}

extern short	simulation_main(void)
{
	useconds_t	next_check;

	stopwatch_start();
	if (!simulation_init())
	{
		write(STDERR_FILENO, "Thread initialisation failed.\n", 31);
		return (EXIT_FAILURE);
	}
	while ((next_check = watch_over_mortals()))
		wait_until(next_check);
	simulation_abort();
	stopwatch_stop();
	return (EXIT_SUCCESS);
}
