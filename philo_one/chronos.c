/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:24:47 by abaur             #+#    #+#             */
/*   Updated: 2021/02/11 16:14:07 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chronos.h"
#include <sys/time.h>

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
