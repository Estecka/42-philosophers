/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 17:32:55 by abaur             #+#    #+#             */
/*   Updated: 2021/02/21 16:00:34 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>

typedef enum e_phistatus	t_phistatus;
enum	e_phistatus
{
	phi_dead = 0,
	phi_sleeping = 1,
	phi_thinking = 2,
	phi_eating = 3,
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
** @var t_mutex self	A mutex protecting some of the philosopher's variables.
** 	Locking this mutex grants access to `meal`, `ttaction` and `ttdie`.
** 	The main thread require this lock to read, but may not write in any case.
** 	The philosopher's thread require this lock to write, but may read without lo
** cking.
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
	pthread_mutex_t	self;

# ifdef philo_one

	pthread_mutex_t	*hands[2];

# else

	unsigned long	hands;

# endif

};

/*
** They're philosophers. The eating kind.
*/

t_philosopher	*g_hoomans;

void	*philo_main(t_philosopher *this);

/*
** Creates a gathering of little men.
** Philosophers are marked as dead until their thread is started.
*/

short	philo_init(int count);

/*
** Disbands the gathering of philosophical thinkers.
** The simulation is expected to be already stopped.
*/

void	philo_deinit();

#endif
