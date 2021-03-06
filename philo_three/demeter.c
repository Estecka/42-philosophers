/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demeter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:33:55 by abaur             #+#    #+#             */
/*   Updated: 2021/03/06 20:00:34 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "demeter.h"

#include "chronos.h"
#include "main.h"
#include "minilibft/minilibft.h"

#include <stdlib.h>

extern int	demeter_main(t_simdash *this)
{
	wait_until(g_ttdie);
	hermes_send(this->sim_abort, 1);
	stopwatch_stop();
	debug(0, "%5u Simulation stopped", stopwatch_date() / MS2USEC);
	return (EXIT_SUCCESS);
}