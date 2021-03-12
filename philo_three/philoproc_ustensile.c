/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoproc_ustensile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:43:04 by abaur             #+#    #+#             */
/*   Updated: 2021/03/12 17:08:46 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoproc_ustensile.h"

#include "main.h"
#include "sustenance_ustensile.h"

extern void	philo_grab_ustensiles(t_philoproc *this)
{
	sem_wait(g_ustensiles);
	this->hands++;
	sem_wait(g_ustensiles);
	this->hands++;
}

extern void	philo_drop_ustensiles(t_philoproc *this)
{
	while (0 < this->hands)
	{
		sem_post(g_ustensiles);
		this->hands--;
	}
}
