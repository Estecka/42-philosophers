/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demeter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:33:55 by abaur             #+#    #+#             */
/*   Updated: 2021/03/08 18:39:24 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "demeter.h"

#include "chronos.h"
#include "logos.h"
#include "main.h"
#include "minilibft/minilibft.h"

#include <stdlib.h>

extern int	demeter_main(t_simdash *this)
{
	while (!usleep(1 * MS2USEC))
	{
		if (this->fulfillment.value == g_philocount)
		{
			debug(0, "   -- All philosophers are fulfilled\n");
			break ;
		}
	}
	logos_silence();
	hermes_send(&this->sim_abort, g_philocount);
	stopwatch_stop();
	debug(0, "   -- Simulation stopped\n");
	return (EXIT_SUCCESS);
}