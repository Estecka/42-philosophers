/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:24:47 by abaur             #+#    #+#             */
/*   Updated: 2021/02/18 17:46:51 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chronos.h"

#include "minilibft/minilibft.h"

#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define FRAMEPERIOD 500

static unsigned short	g_isrunning = 0;
static pthread_t		g_thread = (pthread_t){ 0 };
static __useconds_t		g_date[2] = {0, 0};
static unsigned short	g_i = 0;

static void				*stopwatch_main(void *arg)
{
	(void)arg;
	while (g_isrunning)
	{
		usleep(FRAMEPERIOD);
		g_date[!g_i] = g_date[g_i] + FRAMEPERIOD;
		g_i = !g_i;
	}
	return (NULL);
}

extern void				stopwatch_start(void)
{
	g_isrunning = TRUE;
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

extern __useconds_t		wait_until(__useconds_t target_date)
{
	__useconds_t	current_date;

	while((current_date = stopwatch_date()) < target_date)
		usleep(smallest(1000, target_date - current_date));
	return (stopwatch_date());
}
