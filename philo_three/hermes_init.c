/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hermes_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:22:36 by abaur             #+#    #+#             */
/*   Updated: 2021/03/07 18:18:59 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hermes.h"

#include "minilibft/minilibft.h"

#include <stdlib.h>

static void				hermsender_init(t_hermsender *this, unsigned int dups)
{
	this->duplicatas = dups;
	omnilock_init(&this->locks);
	sem_wait(this->locks.semaphore);
}

extern void				hermsender_destroy(t_hermsender *this)
{
	omnilock_deinit(&this->locks);
}

static void				hermreceiver_init(t_hermreceiver *this, sem_t *sem,
unsigned int datamax)
{
	this->autostop = datamax;
	this->semaphore = sem;
	this->thread = (pthread_t){ 0 };
	this->value = 0;
}

extern void				hermreceiver_destroy(t_hermreceiver *this)
{
	hermreceiver_stop(this);
	this->thread = 0;
	this->autostop = 0;
}

extern void			hermes_init(t_hermpipe *this, unsigned int dups,
unsigned int datamax)
{
	this->duplicatas = dups;
	hermsender_init(&this->sender, dups);
	hermreceiver_init(&this->receivers, this->sender.locks.semaphore, datamax);
}
