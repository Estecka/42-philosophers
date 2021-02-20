/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_ustensile.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:43:04 by abaur             #+#    #+#             */
/*   Updated: 2021/02/16 15:49:01 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_ustensile.h"

#include "main.h"
#include "sustenance_ustensile.h"

extern void	philo_grab_ustensiles(t_philosopher *this)
{
	int				i;
	unsigned short	odd;
	unsigned int	target;

	odd = this->uid & 1;
	i = -1;
	while (++i < 2)
	{
		target = (odd != i) + this->uid;
		if (target == g_philocount)
			target = 0;
		pthread_mutex_lock(&g_ustensiles[target]);
		this->hands[i] = &g_ustensiles[target];
	}
}

extern void	philo_drop_ustensiles(t_philosopher *this)
{
	if (this->hands[0])
		pthread_mutex_unlock(this->hands[0]);
	if (this->hands[1])
		pthread_mutex_unlock(this->hands[1]);
	this->hands[0] = NULL;
	this->hands[1] = NULL;
}
