/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:24:47 by abaur             #+#    #+#             */
/*   Updated: 2021/02/16 16:15:46 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chronos.h"

#include <unistd.h>
#include <sys/time.h>

#define WAITSAFEFTYBUFFER 1000

static struct timeval	g_origin;

/*
** Set the current date as the origin of times.
*/

extern void				stopwatch_start(void)
{
	gettimeofday(&g_origin, NULL);
}

/*
** Gives the time in microseconds since the beginning.
** @return __useconds_t
*/

extern __useconds_t		stopwatch_date(void)
{
	struct timeval	date;

	gettimeofday(&date, NULL);
	return (1000000 * (date.tv_sec - g_origin.tv_sec))
	+ (date.tv_usec - g_origin.tv_usec);
}

extern __useconds_t		wait_until(__useconds_t target_date)
{
	__useconds_t current_date;
	__useconds_t sleep_date;

	if (0 <= WAITSAFEFTYBUFFER && WAITSAFEFTYBUFFER < target_date)
	{
		sleep_date = target_date - WAITSAFEFTYBUFFER;
		current_date = stopwatch_date();
		if (current_date < sleep_date)
			usleep(sleep_date - current_date);
	}
	while ((current_date = stopwatch_date()) < target_date)
		continue ;
	return (current_date);
}
