/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_builder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:27:40 by abaur             #+#    #+#             */
/*   Updated: 2021/03/17 22:50:54 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation_builder.h"

#include "main.h"
#include "minilibft/minilibft.h"

#include <stdlib.h>
#include <sys/wait.h>

static void		sim_init_philo(t_simbuilder *this, unsigned int i)
{
	this->philos[i] = (t_philoproc){0};
	this->philos[i].uid = i;
	this->philos[i].status = phi_sleeping;
	this->philos[i].ttdie = g_ttdie;
	this->philos[i].ttaction = (i % 2) * g_tteat;
	this->philos[i].meals = 0;
	this->philos[i].sim_abort = this->sim_abort.receivers;
	this->philos[i].isfulfilled = this->fulfillment.sender;
	hermes_init(&this->deathes, 1);
	this->philos[i].isdead = this->deathes.sender;
	this->dashboard.deathes[i] = this->deathes.receivers;
	if (g_philocount % 2)
		this->philos[i].nextfast = (i + 1) / 2;
	else
		this->philos[i].nextfast = -1;
}

extern short	sim_init(t_simbuilder *this)
{
	unsigned int	i;

	this->philos = malloc(sizeof(t_philoproc) * g_philocount);
	this->dashboard.processes = malloc(sizeof(pid_t*) * g_philocount);
	this->dashboard.deathes = malloc(sizeof(t_hermreceiver) * g_philocount);
	if (!this->philos || !this->dashboard.processes || !this->dashboard.deathes)
		throw(errno, "[FATAL] Malloc failed in `sim_init`.");
	hermes_init(&this->sim_abort, 1);
	hermes_init(&this->fulfillment, g_philocount);
	this->dashboard.sim_abort = this->sim_abort.sender;
	this->dashboard.fulfillment = this->fulfillment.receivers;
	i = -1;
	while (++i < g_philocount)
		sim_init_philo(this, i);
	return (TRUE);
}

extern void		sim_destroy(t_simbuilder *this)
{
	unsigned int	i;

	hermsender_destroy(&this->dashboard.sim_abort);
	i = -1;
	while (++i < g_philocount)
	{
		hermreceiver_destroy(&this->philos[i].sim_abort);
		hermreceiver_destroy(&this->dashboard.deathes[i]);
		hermsender_destroy(&this->philos[i].isdead);
		hermsender_destroy(&this->philos[i].isfulfilled);
	}
	free(this->philos);
	free(this->dashboard.processes);
	free(this->dashboard.deathes);
}
