/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omnilock.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:13:50 by abaur             #+#    #+#             */
/*   Updated: 2021/02/24 19:53:11 by abaur            ###   ########.fr       */
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

	char			sem_uid[5];
	sem_t			*semaphore;

# endif
};

short	omnilock_mutexinit(t_omnilock *lock);
void	omnilock_deinit(t_omnilock *lock);
void	omnilock_lockup(t_omnilock *lock);
void	omnilock_unlock(t_omnilock *lock);



#endif