/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:27:40 by abaur             #+#    #+#             */
/*   Updated: 2021/03/06 17:09:26 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_builder.h"

#include "main.h"
#include "minilibft/minilibft.h"

#include <stdlib.h>
#include <sys/wait.h>

extern short			sim_init(t_simbuilder *this)
{
	this->philos = malloc(sizeof(t_philoproc) * g_philocount);
	this->dashboard.processes = malloc(sizeof(pid_t*) * g_philocount);
	if (!this->philos || !this->dashboard.processes)
		throw(errno, "[FATAL] Malloc failed in `sim_init`.");
	new_hermes(&this->sim_abort, g_philocount, 1);
	this->dashboard.sim_abort = this->sim_abort.sender;
	this->sim_abort.sender = NULL;
	for (unsigned int i=0; i<g_philocount; i++)
	{
		this->philos[i].uid = i;
		this->philos[i].sim_abort = this->sim_abort.receivers[i];
		this->sim_abort.receivers[i] = NULL;
	}
	free(this->sim_abort.receivers);
	return (TRUE);
}

extern void			sim_destroy(t_simbuilder *this)
{
	hermsender_destroy(this->dashboard.sim_abort);
	for (unsigned int i=0; i<g_philocount; i++)
	{
		hermreceiver_destroy(this->philos[i].sim_abort);
	}
	free(this->philos);
	free(this->dashboard.processes);
}
