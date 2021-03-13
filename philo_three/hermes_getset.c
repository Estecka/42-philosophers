/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hermes_getset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:29:51 by abaur             #+#    #+#             */
/*   Updated: 2021/03/13 18:17:38 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hermes.h"

#include "minilibft/minilibft.h"

extern void			hermes_send(t_hermsender *this, unsigned int amount)
{
	while (amount--)
	{
		if (sem_post(this->locks.semaphore))
		{
			debug(errno, "[ERR] Failed to send event through #%8.8s\n",
				this->locks.sem_uid);
			break ;
		}
	}
}

extern unsigned int	hermes_receive(t_hermreceiver *this)
{
	unsigned int	r;

	if (this->value)
	{
		r = this->value;
		this->value -= r;
		return (r);
	}
	return (0);
}
