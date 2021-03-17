/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_ustensile.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:43:04 by abaur             #+#    #+#             */
/*   Updated: 2021/03/17 21:51:08 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_ustensile.h"

#include "main.h"
#include "chronos.h"
#include "sustenance_ustensile.h"
#include "simulation.h"

#include <stdio.h>

#ifdef philo_one

extern void	philo_grab_ustensiles(t_philosopher *this)
{
	int	target;

	target = (this->uid + 1) % g_philocount;
	pthread_mutex_lock(&g_ustensiles[target]);
	if (g_sim_status == sim_playing)
		printf("%5li %i has taken a fork\n",
			(long)stopwatch_date() / MS2USEC, this->uid);
	this->hands[1] = &g_ustensiles[target];
	target = this->uid;
	pthread_mutex_lock(&g_ustensiles[target]);
	if (g_sim_status == sim_playing)
		printf("%5li %i has taken a fork\n",
			(long)stopwatch_date() / MS2USEC, this->uid);
	this->hands[0] = &g_ustensiles[target];
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

#else

extern void	philo_grab_ustensiles(t_philosopher *this)
{
	sem_wait(g_ustensiles);
	if (g_sim_status == sim_playing)
		printf("%5li %i has taken a fork\n",
			(long)stopwatch_date() / MS2USEC, this->uid);
	this->hands++;
	sem_wait(g_ustensiles);
	if (g_sim_status == sim_playing)
		printf("%5li %i has taken a fork\n",
			(long)stopwatch_date() / MS2USEC, this->uid);
	this->hands++;
}

extern void	philo_drop_ustensiles(t_philosopher *this)
{
	while (0 < this->hands)
	{
		sem_post(g_ustensiles);
		this->hands--;
	}
}

#endif
