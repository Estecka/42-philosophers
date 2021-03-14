/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thanatos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:40:55 by abaur             #+#    #+#             */
/*   Updated: 2021/03/14 15:36:50 by abaur            ###   ########.fr       */
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
	suseconds_t		current_date;

	omnilock_lockup(&philo->self);
	current_date = stopwatch_date();
	if (philo->ttdie <= current_date
		&& !(philo->status == phi_eating && philo->ttaction <= philo->ttdie))
	{
		simulation_emergency_brakes();
		printf("%5u %i died.\n", philo->ttdie / 1000, philo->uid);
		dst->isdead = TRUE;
		dst->next_check = current_date;
		omnilock_unlock(&philo->self);
		return (FALSE);
	}
	dst->isfulfilled = (0 <= g_eatgoal && (g_eatgoal <= (int)philo->meals));
	omnilock_unlock(&philo->self);
	dst->isdead = FALSE;
	dst->next_check = philo_starve_date(philo);
	if (!dst->isfulfilled)
	{
		dst->next_check = smallest(dst->next_check, philo_stuffed_date(philo));
		dst->next_check = greatest(dst->next_check, 10000);
	}
	return (TRUE);
}

extern useconds_t	watch_over_mortals(void)
{
	t_philo_medcheck	medcheck;
	useconds_t			next_check;
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
		printf("%5li All philosophers are fulfilled.\n",
			stopwatch_date() / 1000);
		return (0);
	}
	return (next_check);
}
