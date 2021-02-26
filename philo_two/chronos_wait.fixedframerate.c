/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos_wait.fixedframerate.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:56:45 by abaur             #+#    #+#             */
/*   Updated: 2021/02/26 15:53:44 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chronos.h"

#ifdef FIXEDFRAMERATE

# include "minilibft/minilibft.h"

extern useconds_t		wait_until(useconds_t target_date)
{
	useconds_t	current_date;

	while ((current_date = stopwatch_date()) < target_date
		&& g_stopwatch_running)
		usleep(smallest(250, target_date - current_date) * g_perfs);
	return (stopwatch_date());
}

#endif
