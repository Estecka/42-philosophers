/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omnilock.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:13:50 by abaur             #+#    #+#             */
/*   Updated: 2021/03/06 20:59:14 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** A unified interface to create and manipulate mutex-like structures, regardles
** s on whether the subjects allows for mutices or semaphores.
*/

#ifndef OMNILOCK_H
# define OMNILOCK_H

# include <pthread.h>
# include <semaphore.h>

typedef struct s_omnilock	t_omnilock;

struct	s_omnilock
{
# ifdef philo_one

	pthread_mutex_t	mutex;

# else

	char			sem_uid[9];
	sem_t			*semaphore;

# endif

};

/*
** Create a new mutex/semaphore.
*/

short	omnilock_init(t_omnilock *lock);

/*
** Destroys the mutex/semaphore associated with this omnilock.
*/

void	omnilock_deinit(t_omnilock *lock);

/*
** Waits onto the mutex/semaphore.
*/

void	omnilock_lockup(t_omnilock *lock);

/*
** Posts to the mutex/semaphore.
*/

void	omnilock_unlock(t_omnilock *lock);

# ifndef philo_one

/*
** Destroys all the semaphores that were ever created here.
** This will cause ominlocks to no longer work properly, so only use this before
**  exiting the program entirely.
*/

void	omnilock_destroy_all(void);

# endif

#endif
