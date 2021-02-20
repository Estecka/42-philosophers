/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:05:26 by abaur             #+#    #+#             */
/*   Updated: 2021/02/19 16:17:31 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "philosopher_ustensile.h"

#include "chronos.h"
#include "main.h"
#include "simulation.h"
#include "minilibft/minilibft.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void	philo_sleep(t_philosopher *this)
{
	__useconds_t	date;

	date = wait_until(this->ttaction);
	pthread_mutex_lock(&this->self);
	if (g_sim_status == sim_playing)
	{
		printf("%5i %i is thinking	(+%.3f)\n",
			date / 1000, this->uid, (date - this->ttaction) / (float)1000);
		this->ttaction = date + g_ttsleep;
		this->status = phi_thinking;
	}
	else
		this->status = phi_dead;
	pthread_mutex_unlock(&this->self);
}

static void	philo_think(t_philosopher *this)
{
	__useconds_t	date;

	philo_grab_ustensiles(this);
	pthread_mutex_lock(&this->self);
	date = stopwatch_date();
	if (g_sim_status == sim_playing)
	{
		printf("%5i %i is eating\n", date / 1000, this->uid);
		this->ttaction = date + g_tteat;
		this->status = phi_eating;
	}
	else
		this->status = phi_dead;
	pthread_mutex_unlock(&this->self);
}

static void	philo_eat(t_philosopher *this)
{
	__useconds_t	date;

	date = wait_until(this->ttaction);
	philo_drop_ustensiles(this);
	pthread_mutex_lock(&this->self);
	this->ttdie = this->ttaction + g_ttdie;
	this->meals++;
	if (g_sim_status == sim_playing)
	{
		printf("%5i %i is sleeping	(+%.3f)\n",
			date / 1000, this->uid, (date - this->ttaction) / (float)1000);
		this->ttaction = date + g_ttsleep;
		this->status = phi_sleeping;
	}
	else
		this->status = phi_dead;
	pthread_mutex_unlock(&this->self);
}

extern void	*philo_main(t_philosopher *this)
{
	this->status = phi_sleeping;
	while (g_sim_status == sim_playing)
	{
		if (this->status == phi_eating)
			philo_eat(this);
		else if (this->status == phi_thinking)
			philo_think(this);
		else if (this->status == phi_sleeping)
			philo_sleep(this);
		else
			break ;
	}
	philo_drop_ustensiles(this);
	return (NULL);
}
