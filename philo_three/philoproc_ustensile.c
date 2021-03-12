/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoproc_ustensile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:43:04 by abaur             #+#    #+#             */
/*   Updated: 2021/03/12 17:43:25 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philoproc_ustensile.h"

#include "main.h"
#include "chronos.h"
#include "logos.h"
#include "sustenance_ustensile.h"

extern void	philo_grab_ustensiles(t_philoproc *this)
{
	sem_wait(g_ustensiles);
	philo_log(-1, stopwatch_date(), this->uid, "has grabbed one fork");
	this->hands++;
	sem_wait(g_ustensiles);
	philo_log(-1, stopwatch_date(), this->uid, "has grabbed two forks");
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
