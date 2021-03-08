/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:25:45 by abaur             #+#    #+#             */
/*   Updated: 2021/03/08 17:52:43 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_builder.h"

#include "chronos.h"
#include "demeter.h"
#include "main.h"
#include "minilibft/minilibft.h"
#include "omnilock.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern noreturn void	mutate_demeter(t_simbuilder *this)
{
	int	status;

	hermreceiver_start(&this->dashboard.fulfillment);
	status = demeter_main(&this->dashboard);
	hermreceiver_stop(&this->dashboard.fulfillment);
	for (unsigned int i=0; i<g_philocount; i++)
	{
		debug(0, "[INFO] %i Pid %i waiting...\n", i, this->dashboard.processes[i]);
		waitpid(this->dashboard.processes[i], NULL, 0);
		debug(0, "[INFO] %i Pid %i returned !\n", i, this->dashboard.processes[i]);
	}
	sim_destroy(this);
	omnilock_destroy_all();
	exit(status);
}

extern noreturn void	mutate_philo(t_simbuilder *this, t_philoproc *philosopher)
{
	int	status;

	hermreceiver_start(&philosopher->sim_abort);
	status = philoproc_main(philosopher);
	hermreceiver_stop(&philosopher->sim_abort);
	sim_destroy(this);
	exit(status);
}

extern noreturn void	sim_start(t_simbuilder *this)
{
	pid_t	pid;

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
