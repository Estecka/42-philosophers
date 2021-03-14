/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.sleep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 14:09:41 by abaur             #+#    #+#             */
/*   Updated: 2021/03/12 18:09:21 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chronos.h"

#ifndef FIXEDFRAMERATE

# include "minilibft/minilibft.h"
# include "sys/time.h"

float					g_perfs = 1.0;
unsigned short			g_stopwatch_running = FALSE;

static struct timeval	g_origin;

extern void				stopwatch_start(void)
{
	gettimeofday(&g_origin, NULL);
	g_origin.tv_sec++;
	g_stopwatch_running = TRUE;
}

extern void				stopwatch_stop(void)
{
	g_stopwatch_running = FALSE;
}

extern suseconds_t		stopwatch_date(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - g_origin.tv_sec) * 1000000)
	+ (current_time.tv_usec - g_origin.tv_usec);
}

# ifdef MACROSLEEP

extern useconds_t		wait_until(useconds_t target_date)
{
	useconds_t	current_date;

	while ((current_date = stopwatch_date()) < target_date
		&& g_stopwatch_running)
		usleep(target_date - current_date);
	return (current_date);
}

# elif defined MICROSLEEP

extern suseconds_t		wait_until(useconds_t target_date)
{
	suseconds_t	current_date;

	while ((current_date = stopwatch_date()) < target_date
		&& g_stopwatch_running)
		usleep(smallest(1000, target_date - current_date));
	return (current_date);
}

# endif

#endif
