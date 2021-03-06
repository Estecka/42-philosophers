/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hermes_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:22:36 by abaur             #+#    #+#             */
/*   Updated: 2021/03/06 21:11:11 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hermes.h"

#include "minilibft/minilibft.h"

#include <stdlib.h>

static t_hermsender		*new_hermsender(unsigned int dups)
{
	t_hermsender	*this;
	unsigned int	i;

	this = malloc(sizeof(t_hermsender) + (sizeof(t_omnilock) * dups));
	if (!this)
		return (NULL);
	this->duplicatas = dups;
	this->locks = ((void*)this) + (sizeof(t_hermsender));
	i = -1;
	while (++i < dups)
	{
		omnilock_init(&this->locks[i]);
		sem_wait(this->locks[i].semaphore);
	}
	return (this);
}

extern void				hermsender_destroy(t_hermsender *this)
{
	unsigned int	i;

	i = -1;
	while (++i < this->duplicatas)
		omnilock_deinit(&this->locks[i]);
	free(this);
}

static t_hermreceiver	*new_hermreceiver(sem_t *sem, unsigned int datamax)
{
	t_hermreceiver	*this;

	this = malloc(sizeof(t_hermreceiver));
	if (!this)
		return (NULL);
	this->autostop = datamax;
	this->semaphore = sem;
	this->thread = (pthread_t){ 0 };
	this->value = 0;
	return (this);
}

extern void				hermreceiver_destroy(t_hermreceiver *this)
{
	hermreceiver_stop(this);
	free(this);
}

extern short			new_hermes(t_hermpipe *this, unsigned int dups,
unsigned int max)
{
	unsigned int	i;

	this->duplicatas = dups;
	this->sender = new_hermsender(dups);
	if (!this->sender)
		throw(errno, "[FATAL] Failed to initialize a Hermsender.");
	this->receivers = malloc(sizeof(t_hermreceiver*) * (dups + 1));
	if (!this->receivers)
		throw(errno, "[FATAL] Failed to initialize an array of Hermreceivers.");
	i = -1;
	while (++i < dups)
	{
		this->receivers[i] = new_hermreceiver(
			this->sender->locks->semaphore, max);
		if (!this->receivers[i])
			throw(errno, "[FATAL] Failed to initialize a Hermreceiver.");
	}
	this->receivers[dups] = NULL;
	return (TRUE);
}
