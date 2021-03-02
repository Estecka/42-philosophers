/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omnilock.semaphore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:24:51 by abaur             #+#    #+#             */
/*   Updated: 2021/02/28 00:14:35 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philo_one

# include "omnilock.h"

# include "minilibft/minilibft.h"

# include <fcntl.h>
# include <sys/stat.h>

static unsigned int	g_semcount = 0x00000000;

extern short		omnilock_init(t_omnilock *lock)
{
	miniitoahex(lock->sem_uid, g_semcount++);
	sem_unlink(lock->sem_uid);
	lock->semaphore = sem_open(lock->sem_uid,
		O_CREAT | O_EXCL,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,
		1);
	if (lock->semaphore == SEM_FAILED)
		throw(errno, "[FATAL] Failed to initialize semaphore 0x%08x",
			g_semcount - 1);
	return (lock->semaphore != SEM_FAILED);
}

extern void			omnilock_deinit(t_omnilock *lock)
{
	sem_unlink(lock->sem_uid);
	sem_close(lock->semaphore);
	lock->semaphore = NULL;
}

extern void			omnilock_lockup(t_omnilock *lock)
{
	sem_wait(lock->semaphore);
}

extern void			omnilock_unlock(t_omnilock *lock)
{
	sem_post(lock->semaphore);
}

#endif
