/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos_test_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:52:06 by abaur             #+#    #+#             */
/*   Updated: 2021/02/15 21:21:19 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chronos.h"
#include "minilibft/minilibft.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static __useconds_t	g_sleeptime;

static void	*thread_main(void *uid)
{
	__useconds_t	target_date;
	__useconds_t	wake_date;

	while (1)
	{
		target_date = stopwatch_date() + g_sleeptime;
		wake_date = wait_until(target_date);
		printf("%i Latency: %+.3f ms\n", (int)uid,
			(wake_date - target_date)/(float)1000);
	}
}

extern int	main(int argc, char **args)
{
	unsigned int	threads;
	pthread_t		trashbin;

	threads = (argc >= 2) ?
		greatest(1, miniatoi(args[1])) :
		0;
	g_sleeptime = (argc >= 3) ?
		miniatoi(args[2]) * 1000 :
		1000000;
	stopwatch_start();
	while(threads--)
		pthread_create(&trashbin, NULL, &thread_main, (void*)threads);
	thread_main(0);
}
