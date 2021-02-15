/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:24:50 by abaur             #+#    #+#             */
/*   Updated: 2021/02/15 21:01:31 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHRONOS_H
# define CHRONOS_H

# include <unistd.h>

# define MS2USEC 1000
# define USEC2MS 0.001

/*
** Set the current date as the origin of times.
*/

void			stopwatch_start(void);

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
