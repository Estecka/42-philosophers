/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:24:50 by abaur             #+#    #+#             */
/*   Updated: 2021/02/18 17:13:19 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHRONOS_H
# define CHRONOS_H

# include <unistd.h>

# define MS2USEC 1000
# define USEC2MS 0.001

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
