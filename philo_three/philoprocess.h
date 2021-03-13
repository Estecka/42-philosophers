/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoprocess.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:58:54 by abaur             #+#    #+#             */
/*   Updated: 2021/03/13 16:58:18 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOPROCESS_H
# define PHILOPROCESS_H

#include "hermes.h"

#include <pthread.h>
#include <unistd.h>

typedef enum e_phistatus	t_phistatus;
enum	e_phistatus
{
	phi_dead = 0,
	phi_sleeping = 1,
	phi_thinking = 2,
	phi_eating = 3,
};

/*
** @var unsigned int uid	The unique id of the philsopher.
** @var t_phistatus status	The ongoing action of the philosopher.
** @var useconds_t ttaction	The date when the ongoing action will be completed.
** @var useconds_t ttaction	The date when the philosopher will starve to death.
** @var unsigned int meals	The amount of times the philosopher has finished a m
** eal.
** @var unsigned int hands	The amount of eating ustensiles this philosopher has
**  grabbed.
**
** @var pthread_t minithan	The thread id of the mini-thanatos watching over thi
** s philosopher.
**
** @var t_hermreceiver sim_abort	Listens for the eventual abortion of the sim
** ulation.
** @var t_hermsender isfulfilled	Event to send once the philosopher is fulfil
** led.
** @var t_hermsender isdead	Event to send once the philosopher has starved.
*/

typedef struct s_philoproc	t_philoproc;
struct	s_philoproc
{
	unsigned int	uid;
	t_phistatus		status;
	useconds_t		ttaction;
	useconds_t		ttdie;
	unsigned int	meals;
	unsigned int	hands;

	pthread_t		minithan;

	t_hermreceiver	sim_abort;
	t_hermsender	isfulfilled;
	t_hermsender	isdead;
};

int		philoproc_main(t_philoproc *this);

#endif