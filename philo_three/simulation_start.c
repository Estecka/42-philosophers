/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:25:45 by abaur             #+#    #+#             */
/*   Updated: 2021/03/13 17:22:07 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_builder.h"

#include "chronos.h"
#include "demeter.h"
#include "logos.h"
#include "main.h"
#include "minithanatos.h"
#include "minilibft/minilibft.h"
#include "omnilock.h"
#include "sustenance_ustensile.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern noreturn void	mutate_demeter(t_simbuilder *this)
{
	int	status;

	for (unsigned int i=0; i<g_philocount; i++)
		hermreceiver_start(&this->dashboard.deathes[i]);
	hermreceiver_start(&this->dashboard.fulfillment);
	status = demeter_main(&this->dashboard);
	hermreceiver_stop(&this->dashboard.fulfillment);
	for (unsigned int i=0; i<g_philocount; i++)
	{
		hermreceiver_stop(&this->dashboard.deathes[i]);
		debug(0, "[INFO] %i Pid %i waiting...\n", i, this->dashboard.processes[i]);
		waitpid(this->dashboard.processes[i], NULL, 0);
		debug(0, "[INFO] %i Pid %i returned !\n", i, this->dashboard.processes[i]);
	}
	ustensile_deinit();
	// sem_unlink("Instruments of Sustenance");
	logos_deinit();
	sim_destroy(this);
	omnilock_destroy_all();
	exit(status);
}

static void				philo_silence(t_hermreceiver *hermes, void *philo)
{
	(void)hermes;
	logos_silence();
	debug(0, "%5li %i was Silenced\n",
		stopwatch_date() / MS2USEC, ((t_philoproc*)philo)->uid);
	((t_philoproc*)philo)->status = phi_dead;
	stopwatch_stop();
}

extern noreturn void	mutate_philo(t_simbuilder *this, t_philoproc *philosopher)
{
	int	status;

	philosopher->sim_abort.reaction = &philo_silence;
	philosopher->sim_abort.reaction_arg = philosopher;
	hermreceiver_start(&philosopher->sim_abort);
	minithanatos_start(philosopher);
	status = philoproc_main(philosopher);
	minithanatos_stop(philosopher);
	hermreceiver_stop(&philosopher->sim_abort);
	logos_deinit();
	sim_destroy(this);
	ustensile_deinit();
	exit(status);
}

extern noreturn void	sim_start(t_simbuilder *this)
{
	pid_t	pid;

	ustensile_init(g_philocount);
	logos_init();
	stopwatch_start();
	for (unsigned int i=0; i<g_philocount; i++)
	{
		pid = fork();
		if (pid < 0)
		{
			hermes_send(&this->sim_abort.sender, g_philocount);
			throw(errno, "[FATAL] Failed fo fork philo n°%i", i);
		}
		if (!pid)
			mutate_philo(this, &this->philos[i]);
		this->dashboard.processes[i] = pid;
	}
	mutate_demeter(this);
}
