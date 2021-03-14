/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demeter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:33:55 by abaur             #+#    #+#             */
/*   Updated: 2021/03/14 17:22:37 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "demeter.h"

#include "chronos.h"
#include "logos.h"
#include "main.h"
#include "minilibft/minilibft.h"

#include <stdlib.h>
#include <stdio.h>

extern int	demeter_main(t_simdash *this)
{
	unsigned int	i;

	while (!usleep(1 * MS2USEC))
	{
		if (this->fulfillment.value == g_philocount)
		{
			hermes_send(&this->sim_abort, g_philocount);
			debug(0, "   -- All philosophers are fulfilled\n");
			break ;
		}
		i = -1;
		while (++i < g_philocount)
			if (this->deathes[i].value)
			{
				hermes_send(&this->sim_abort, g_philocount);
				philo_log(-1, stopwatch_date(), i, "died");
				break ;
			}
		if (i < g_philocount)
			break ;
	}
	logos_silence();
	stopwatch_stop();
	debug(0, "   -- Simulation stopped\n");
	return (EXIT_SUCCESS);
}
