/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hermes_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:00:06 by abaur             #+#    #+#             */
/*   Updated: 2021/03/08 17:42:33 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hermes.h"

#include "minilibft/minilibft.h"

static void		*hermreceiver_main(t_hermreceiver *this)
{
	int	status;

	while(this->autostop)
	{
		status = sem_wait(this->semaphore);
		if (status)
			debug(errno, "[ERR] Failed to listen to a semaphore.\n");
		if (!status && this->autostop)
		{
			this->value++;
			this->autostop--;
			if (this->reaction)
				this->reaction(this, this->reaction_arg);
		}
	}
	return (NULL);
}

extern short	hermreceiver_start(t_hermreceiver *this)
{
	int	status;

	if (this->thread)
		return (TRUE);
	status = pthread_create(&this->thread, NULL,
		(void*(*)(void*))&hermreceiver_main, this);
	if (status)
	{
		this->thread = 0;
		throw(status, "[FATAL] Failed to create HermReceiver thread");
	}
	return (TRUE);
}

extern void		hermreceiver_stop(t_hermreceiver *this)
{
	if (this->thread != 0)
	{
		this->autostop = 0;
		sem_post(this->semaphore);
		pthread_join(this->thread, NULL);
		this->thread = 0;
	}
}
