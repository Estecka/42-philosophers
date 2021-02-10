/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:32:55 by abaur             #+#    #+#             */
/*   Updated: 2021/02/10 17:01:35 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>

typedef enum e_phistatus	t_phistatus;
enum	e_phistatus
{
	phi_dead = 0,
	phi_sleep = 1,
	phi_think = 2,
	phi_eat = 3,
};

/*
** A little man who sleeps and eats all day long.
** @var int uid	The unique identifiant of the philosopher
** @var pthread_t	The thread the philosopher is running on.
** @var t_phistatus status	The current state of the philosopher
** @var int meals	The amount of meals the little man has finished eating.
** @var int ttaction	The date in microseconds when the philosopher will compl
** ete its ongoing action.
** @var int ttdie	The date in microseconds when the philosopher will starve.
** @var t_mutex[2] hands	A pointer to the eating ustensiles the philosopher h
** as grabbed. 0 is its right hand, and 1 its left hand.
*/

typedef struct s_philosopher	t_philosopher;
struct	s_philosopher
{
	unsigned int	uid;
	pthread_t		thread;
	t_phistatus		status;
	unsigned int	meals;
	__useconds_t	ttaction;
	__useconds_t	ttdie;
	pthread_mutex_t	*hands[2];
};

/*
** They're philosophers. The eating kind.
*/

t_philosopher	*g_hoomans;

/*
** Creates a gathering of little men.
** Their first action upon being born will be to think about spaghettis.
*/

short	philo_init(int count);

/*
** Disbands the gathering of philosophical thinkers.
** The simulation is expected to be already stopped.
*/

void	philo_deinit();

#endif
