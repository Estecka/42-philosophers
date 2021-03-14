/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minithanatos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:59:15 by abaur             #+#    #+#             */
/*   Updated: 2021/03/14 16:11:00 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minithanatos.h"

#include "chronos.h"
#include "main.h"
#include "minilibft/minilibft.h"

static void	*minithanatos_main(t_philoproc *philo)
{
	suseconds_t	date;

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
		wait_until(philo->ttdie);
	}
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
