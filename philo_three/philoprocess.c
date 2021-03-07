/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoprocess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:18:14 by abaur             #+#    #+#             */
/*   Updated: 2021/03/07 18:19:26 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoprocess.h"

#include "main.h"
#include "chronos.h"
#include "minilibft/minilibft.h"

#include <stdio.h>
#include <stdlib.h>

extern int	philoproc_main(t_philoproc *this)
{
	useconds_t	date;

	date = stopwatch_date();
	debug(0, "%5u %i I think, therefore, I am", date/MS2USEC, this->uid);
	date = wait_until(date + g_ttsleep);
	while (!this->sim_abort.value)
	{
		printf("%5u %i is eating\n", date / MS2USEC, this->uid);
		date = wait_until(date + g_tteat);
	}
	debug(0, "%5u %i I no longer think, and therefore am no longer", date/MS2USEC, this->uid);
	return (EXIT_SUCCESS);
}
