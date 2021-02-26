/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fated_list_of_minor_prophecies.h                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:49:21 by abaur             #+#    #+#             */
/*   Updated: 2021/02/26 15:38:10 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The minor prophecies of the Three Fates shall come too pass,
** sooner ot later, probably.
*/

#ifndef FATED_LIST_OF_MINOR_PROPHECIES_H
# define FATED_LIST_OF_MINOR_PROPHECIES_H

# include "philosopher.h"
# include <unistd.h>

/*
** A Philosopher Shall Someday Starve To Death.
**
** Computes a low estimation of how long a philosopher will survive. A philosoph
** er is guaranteed to never starve before the returned date, so it is not neede
** d to check again until this date is reached.
** Threads are expected to lock the appropriate mutex before calling this functi
** on.
** @param t_philosopher* this	The philosopher to foresee.
** @return useconds_t	A date until which the philosopher may never starve.
** 	If the philosopher has already starved, this will return a date lower than t
** he current date.
*/

useconds_t	philo_starve_date(t_philosopher *this);

/*
** A Philosopher Shall Someday Finish Their Meal.
**
** Computes a low estimation of how long it will take a philosopher to eat their
**  daily nutritional requirement. A philosopher is guaranteed to never eat enou
** gh until the the returned date is reached, so it is not needed to check to ch
** eck again until this date is reach.
** Threads are expected to lock the appropriate mutex before calling this functi
** on.
** @param t_philosopher this	The philosopher to foresee.
** @return __usecond_t	A date until which a philosopher may never finish eating
** .
** 	This will return 0 if the philosopher is done eating;
** 	This will return -1 if their is no limit to their hunger.
*/

useconds_t	philo_stuffed_date(t_philosopher *this);

#endif
