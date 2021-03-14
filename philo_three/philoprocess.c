/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoprocess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:18:14 by abaur             #+#    #+#             */
/*   Updated: 2021/03/14 19:50:46 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoprocess.h"

#include "main.h"
#include "chronos.h"
#include "logos.h"
#include "minilibft/minilibft.h"
#include "philoproc_ustensile.h"

#include <stdio.h>
#include <stdlib.h>

static void	philoproc_think(t_philoproc *this)
{
	suseconds_t	date;

	philo_grab_ustensiles(this);
	date = stopwatch_date();
	philo_log(-1, date, this->uid, "is eating");
	this->status = phi_eating;
	this->ttaction = date + g_tteat;
}

static void	philoproc_eat(t_philoproc *this)
{
	suseconds_t	date;

	date = wait_until(this->ttaction);
	this->ttdie += g_ttdie;
	philo_log(this->ttaction, date, this->uid, "is sleeping");
	philo_drop_ustensiles(this);
	this->meals++;
	if ((signed)this->meals == g_eatgoal)
	{
		debug(0, "%5u %i is fulfilled\n", (int)date / MS2USEC, this->uid);
		hermes_send(&this->isfulfilled, 1);
	}
	this->status = phi_sleeping;
	this->ttaction += g_ttsleep;
}

static void	philoproc_sleep(t_philoproc *this)
{
	suseconds_t	date;

	date = wait_until(this->ttaction);
	philo_log(this->ttaction, date, this->uid, "is thinking");
	this->status = phi_thinking;
}

extern int	philoproc_main(t_philoproc *this)
{
	debug(0, "   -- %i I think, therefore, I am\n", this->uid);
	while (!this->sim_abort.value && this->status != phi_dead)
	{
		if (this->status == phi_thinking)
			philoproc_think(this);
		else if (this->status == phi_sleeping)
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
