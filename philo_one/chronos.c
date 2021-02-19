/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:24:47 by abaur             #+#    #+#             */
/*   Updated: 2021/02/19 16:02:05 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chronos.h"

#include "minilibft/minilibft.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define FRAMEPERIOD 499
#define PERF_MAX    1.5
#define PERF_MIN    0.8

static unsigned short	g_isrunning = 0;
static pthread_t		g_thread = (pthread_t){ 0 };

static struct timeval	g_origin;
static __useconds_t		g_date[2];
static unsigned short	g_i;

float					g_perfs = 1.2;
static __useconds_t		g_prev_perfcheck = 0;
static __useconds_t		g_next_perfcheck = 2000000;

static void				compute_perfs(void)
{
	struct timeval	current_time;
	__useconds_t	true_time;

	gettimeofday(&current_time, NULL);
	true_time = (current_time.tv_usec - g_origin.tv_usec)
		+ ((current_time.tv_sec - g_origin.tv_sec) * 1000000);
	g_perfs = (float)(true_time - g_prev_perfcheck)
		/ (g_date[g_i] - g_prev_perfcheck);
	g_perfs = clamp(g_perfs, PERF_MIN, PERF_MAX);
	dprintf(STDERR_FILENO, "%5u Performance: %f\n", true_time / 1000, g_perfs);
	g_prev_perfcheck = g_next_perfcheck;
	g_next_perfcheck += 1000000;
}

static void				*stopwatch_main(void *arg)
{
	(void)arg;
	gettimeofday(&g_origin, NULL);
	while (g_isrunning)
	{
		usleep(FRAMEPERIOD / g_perfs);
		g_date[!g_i] = g_date[g_i] + FRAMEPERIOD;
		g_i = !g_i;
		if (g_next_perfcheck < g_date[g_i])
			compute_perfs();
	}
	return (NULL);
}

extern void				stopwatch_start(void)
{
	g_isrunning = TRUE;
	g_date[0] = 0;
	g_date[1] = 0;
	pthread_create(&g_thread, NULL, &stopwatch_main, NULL);
}

extern void				stopwatch_stop(void)
{
	g_isrunning = FALSE;
	pthread_join(g_thread, NULL);
}

/*
** Gives the time in microseconds since the origin of times.
** @return __useconds_t
*/

extern __useconds_t		stopwatch_date(void)
{
	return (g_date[g_i]);
}
