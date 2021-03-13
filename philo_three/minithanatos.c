/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minithanatos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:59:15 by abaur             #+#    #+#             */
/*   Updated: 2021/03/13 18:19:29 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minithanatos.h"

#include "chronos.h"
#include "main.h"
#include "minilibft/minilibft.h"

static void	*minithanatos_main(t_philoproc *philo)
{
	suseconds_t	date;

	debug(0, "   -- %i Death is inescapable\n", philo->uid);
	wait_until(g_ttdie);
	while (!philo->sim_abort.value && philo->status != phi_dead)
	{
		date = stopwatch_date();
		if (date > philo->ttdie)
		{
			hermes_send(&philo->isdead, 1);
			philo->status = phi_dead;
			break ;
		}
		debug(0, "%5lu %i survived, for now...	(%u)\n",
			date / MS2USEC, philo->uid, philo->ttdie / MS2USEC);
		wait_until(philo->ttdie);
	}
	debug(0, "   -- %i death is done.\n", philo->uid);
	return (NULL);
}

extern void	minithanatos_start(t_philoproc *this)
{
	int	err;

	err = pthread_create(&this->minithan, NULL,
		(void*(*)(void*))&minithanatos_main, this);
	if (err)
		throw(err, "[FATAL] Failed to start minithanatos n°%i\n", this->uid);
}

extern void	minithanatos_stop(t_philoproc *this)
{
	if (this->minithan != 0)
		pthread_join(this->minithan, NULL);
	this->minithan = 0;
}
