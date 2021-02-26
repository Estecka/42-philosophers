/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omnilock.mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:13:45 by abaur             #+#    #+#             */
/*   Updated: 2021/02/24 19:57:39 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef philo_one

# include "omnilock.h"

extern short	omnilock_init(t_omnilock *lock)
{
	return (!pthread_mutex_init(&lock->mutex, NULL));
}

extern void		omnilock_deinit(t_omnilock *lock)
{
	pthread_mutex_destroy(&lock->mutex);
}

extern void		omnilock_lockup(t_omnilock *lock)
{
	pthread_mutex_lock(&lock->mutex);
}

extern void		omnilock_unlock(t_omnilock *lock)
{
	pthread_mutex_unlock(&lock->mutex);
}

#endif
