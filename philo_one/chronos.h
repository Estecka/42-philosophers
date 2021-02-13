/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:24:50 by abaur             #+#    #+#             */
/*   Updated: 2021/02/13 14:26:10 by abaur            ###   ########.fr       */
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
** Gives the time in microseconds since the beginning.
*/

__useconds_t	stopwatch_date(void);

/*
** Blocks the thread until the given date is reached.
** @param __useconds_t date	The date to wait for
*/

void			wait_until(__useconds_t date);

#endif
