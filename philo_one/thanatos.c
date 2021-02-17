/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thanatos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:40:55 by abaur             #+#    #+#             */
/*   Updated: 2021/02/17 15:48:12 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thanatos.h"

#include "chronos.h"
#include "fated_list_of_minor_prophecies.h"
#include "main.h"
#include "simulation.h"
#include "minilibft/minilibft.h"

#include <stdio.h>

static short		philo_medcheck(t_philosopher *philo, t_philo_medcheck *dst)
{
	__useconds_t		current_date;

	pthread_mutex_lock(&philo->self);
	current_date = stopwatch_date();
	if (philo->ttdie <= current_date
		&& !(philo->status == phi_eating && philo->ttaction <= philo->ttdie))
	{
		simulation_emergency_brakes();
		printf("%5u %i has died.\n", philo->ttdie / 1000, philo->uid);
		dst->isdead = TRUE;
		dst->next_check = current_date;
		pthread_mutex_unlock(&philo->self);
		return (FALSE);
	}
	else
		dst->isdead = FALSE;
	if (0 <= g_eatgoal && g_eatgoal <= (int)philo->meals)
		dst->isfulfilled = TRUE;
	else
		dst->isfulfilled = FALSE;
	dst->next_check =
		smallest(philo_starve_date(philo), philo_stuffed_date(philo));
	pthread_mutex_unlock(&philo->self);
	return (TRUE);
}

extern __useconds_t	watch_over_mortals(void)
{
	t_philo_medcheck	medcheck;
	__useconds_t		next_check;
	unsigned int		i;
	short				allfulfilled;

	allfulfilled = (0 <= g_eatgoal);
	next_check = -1;
	i = -1;
	while (++i < g_philocount)
	{
		if (!philo_medcheck(&g_hoomans[i], &medcheck))
			return (0);
		allfulfilled &= medcheck.isfulfilled;
		next_check = smallest(next_check, medcheck.next_check);
	}
	if (allfulfilled)
	{
		simulation_emergency_brakes();
		dprintf(STDERR_FILENO, "All philosophers are fulfilled.\n");
		return (0);
	}
	return (next_check);
}
