/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:24:50 by abaur             #+#    #+#             */
/*   Updated: 2021/02/25 17:01:04 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHRONOS_H
# define CHRONOS_H

# include <unistd.h>

/*
** Either one of these should be defined:
** FIXEDFRAMERATE, MACROSLEEP, or MICROSLEEP
**
** 	FIXEDFRAMERATE is the most reliable, but might be considered as cheating, be
** cause it mostly uses simulated time instead of real time. Depending on the ma
** chine's performance, it's susceptible to display noticeable bursts of overclo
** cking/underclocking, or might fall behind considerably compared to real time.
**
** 	MACROSLEEP is more reliable for the VM, but in some rare cases it might stil
** l oversleep for over 10ms.
**
** 	MICROSLEEP is more reliable on Guacamole, and doesn't seem to considerably o
** versleep.
*/

# define MACROSLEEP

# define MS2USEC 1000
# define USEC2MS 0.001

float			g_perfs;
unsigned short	g_stopwatch_running;

void			stopwatch_start(void);

void			stopwatch_stop(void);

/*
** Gives the date in microseconds since the origin of times.
*/

__useconds_t	stopwatch_date(void);

/*
** Blocks the thread until the given date is reached.
** @param __useconds_t date	The date to wait for.
** @return __useconds_t	The date when the function returned.
*/

__useconds_t	wait_until(__useconds_t date);

#endif
