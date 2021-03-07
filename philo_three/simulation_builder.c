/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:27:40 by abaur             #+#    #+#             */
/*   Updated: 2021/03/07 18:53:54 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_builder.h"

#include "main.h"
#include "minilibft/minilibft.h"

#include <stdlib.h>
#include <sys/wait.h>

static void				sim_init_philo(t_simbuilder *this, unsigned int i)
{
	this->philos[i] = (t_philoproc){0};
	this->philos[i].uid = i;
	this->philos[i].status = phi_sleeping;
	this->philos[i].ttaction = 0;
	this->philos[i].meals = 0;
	this->philos[i].sim_abort = this->sim_abort.receivers;
	this->philos[i].isfulfilled = this->fulfillment.sender;
}

extern short			sim_init(t_simbuilder *this)
{
	this->philos = malloc(sizeof(t_philoproc) * g_philocount);
	this->dashboard.processes = malloc(sizeof(pid_t*) * g_philocount);
	if (!this->philos || !this->dashboard.processes)
		throw(errno, "[FATAL] Malloc failed in `sim_init`.");
	hermes_init(&this->sim_abort, g_philocount, 1);
	hermes_init(&this->fulfillment, 1, g_philocount);
	this->dashboard.sim_abort = this->sim_abort.sender;
	this->dashboard.fulfillment = this->fulfillment.receivers;
	for (unsigned int i=0; i<g_philocount; i++)
		sim_init_philo(this, i);
	return (TRUE);
}

extern void			sim_destroy(t_simbuilder *this)
{
	hermsender_destroy(&this->dashboard.sim_abort);
	for (unsigned int i=0; i<g_philocount; i++)
	{
		hermreceiver_destroy(&this->philos[i].sim_abort);
		hermsender_destroy(&this->philos[i].isfulfilled);
	}
	free(this->philos);
	free(this->dashboard.processes);
}
