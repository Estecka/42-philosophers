/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logos.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:33:48 by abaur             #+#    #+#             */
/*   Updated: 2021/03/08 18:39:01 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGOS_H
# define LOGOS_H

/*
** For some reason <semaphore.h> is required to use `suseconds_t`
*/

# include <semaphore.h>
# include <unistd.h>

void	logos_init();
void	logos_deinit();

/*
** Silences the logger, without deinitializing it.
*/

void	logos_silence();

/*
** @param suseconds_t ttaction	The date when the philosopher was expected to ta
** ke action. Or -1 if no specific date was expected.
** @param useconds_t wakedate	The date when the action actually took place.
** @param unsigned int philo_uid	The uid of the philosopher that took action.
** @param const string	The message to be displayed.
*/

void	philo_log(suseconds_t ttaction, useconds_t wakedate,
unsigned int philo_uid, const char *message);

#endif
