/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hermes_getset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:29:51 by abaur             #+#    #+#             */
/*   Updated: 2021/03/02 15:34:59 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hermes.h"

#include "minilibft/minilibft.h"

extern void		hermsender_send(t_hermsender *this, unsigned int amount)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	while (++i < this->duplicatas)
	{
		j = amount;
		while (j--)
		{
			if (sem_post(this->locks[i].semaphore))
			{
				debug(errno, "[ERR] Failed to send event through #%4.5s",
					this->locks->sem_uid);
				break ;
			}
		}
	}
		
}

extern unsigned int	hermreceiver_fetch(t_hermreceiver *this)
{
	unsigned int	r;

	if (this->value)
	{
		r = this->value;
		this->value -=  r;
		return (r);
	}
	return (0);
}