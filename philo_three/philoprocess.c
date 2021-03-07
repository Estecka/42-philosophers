/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoprocess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:18:14 by abaur             #+#    #+#             */
/*   Updated: 2021/03/07 20:02:04 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoprocess.h"

#include "main.h"
#include "chronos.h"
#include "minilibft/minilibft.h"

#include <stdio.h>
#include <stdlib.h>

static void	philoproc_eat(t_philoproc *this)
{
	suseconds_t	date;

	this->ttaction += g_tteat;
	date = wait_until(this->ttaction);
	// this->ttdie += g_ttdie;
	this->status = phi_sleeping;
	printf("%5lu %i is sleeping	(%+.3fms)\n",
		date / MS2USEC, this->uid, (date - this->ttaction) * USEC2MS);
	// drop_ustensile(this);
	this->meals++;
	if ((signed)this->meals == g_eatgoal)
	{
		debug(0, "%5lu %i is fulfilled\n", date / MS2USEC, this->uid);
		hermes_send(&this->isfulfilled, 1);
	}
}

static void	philoproc_sleep(t_philoproc *this)
{
	suseconds_t	date;

	this->ttaction += g_ttsleep;
	date = wait_until(this->ttaction);
	this->status = phi_eating;
	printf("%5lu %i is eating	(%+.3fms)\n",
		date / MS2USEC, this->uid, (date - this->ttaction) * USEC2MS);
}

extern int	philoproc_main(t_philoproc *this)
{
	debug(0, "   -- %i I think, therefore, I am\n", this->uid);
	while (!this->sim_abort.value && this->status != phi_dead)
	{
		if (this->status == phi_sleeping)
			philoproc_sleep(this);
		else if (this->status == phi_eating)
			philoproc_eat(this);
		else
			break ;
	}
	debug(0, "   -- %i I no longer think, and therefore am no longer\n",
		this->uid);
	return (EXIT_SUCCESS);
}
