/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:05:26 by abaur             #+#    #+#             */
/*   Updated: 2021/02/13 17:13:42 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include "chronos.h"
#include "main.h"
#include "simulation.h"
#include "minilibft/minilibft.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void	philo_sleep(t_philosopher *this)
{
	int	ttactionms;

	ttactionms = this->ttaction / 1000;
	wait_until(this->ttaction);
	if (g_sim_status == sim_playing)
	{
		printf("%5i %i is thinking\n", ttactionms, this->uid);
		this->ttaction += g_ttsleep;
		this->status = phi_thinking;
	}
	else
		this->status = phi_dead;
}

static void	philo_think(t_philosopher *this)
{
	int	ttactionms;

	ttactionms = this->ttaction / 1000;
	wait_until(this->ttaction);
	if (g_sim_status == sim_playing)
	{
		printf("%5i %i is eating\n", ttactionms, this->uid);
		this->ttaction += g_tteat;
		this->status = phi_eating;
	}
	else
		this->status = phi_dead;
}

static void	philo_eat(t_philosopher *this)
{
	int	ttactionms;

	ttactionms = this->ttaction / 1000;
	wait_until(this->ttaction);
	this->ttdie = this->ttaction + g_ttdie;
	if (g_sim_status == sim_playing)
	{
		printf("%5i %i is sleeping\n", ttactionms, this->uid);
		this->ttaction += g_ttsleep;
		this->status = phi_sleeping;
	}
	else
		this->status = phi_dead;
}

extern void	*philo_main(t_philosopher *this)
{
	while (g_sim_status == sim_playing)
	{
		pthread_mutex_lock(&this->self);
		if (this->status == phi_eating)
			philo_eat(this);
		else if (this->status == phi_thinking)
			philo_think(this);
		else if (this->status == phi_sleeping)
			philo_sleep(this);
		else
		{
			pthread_mutex_unlock(&this->self);
			break ;
		}
		pthread_mutex_unlock(&this->self);
	}
	return (NULL);
}
