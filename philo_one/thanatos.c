/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thanatos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:40:55 by abaur             #+#    #+#             */
/*   Updated: 2021/02/20 17:37:31 by abaur            ###   ########.fr       */
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
	dst->isfulfilled = (0 <= g_eatgoal && (g_eatgoal <= (int)philo->meals));
	pthread_mutex_unlock(&philo->self);
	dst->isdead = FALSE;
	dst->next_check = philo_starve_date(philo);
	if (!dst->isfulfilled)
		dst->next_check = smallest(dst->next_check, philo_stuffed_date(philo));
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
		if (!medcheck.next_check && !medcheck.isdead)
			printf("Something unexpected happened. This is a crash.\n");
	}
	if (allfulfilled)
	{
		simulation_emergency_brakes();
		printf("%5u All philosophers are fulfilled.\n",
			stopwatch_date() / 1000);
		return (0);
	}
	return (next_check);
}
