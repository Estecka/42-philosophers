/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:07:46 by abaur             #+#    #+#             */
/*   Updated: 2021/03/17 19:59:54 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "philosopher.h"
#include "minilibft/minilibft.h"

#include <pthread.h>
#include <stdlib.h>

static void		philo_mutex_abort(int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		omnilock_deinit(&g_hoomans[i].self);
	}
}

static short	philo_mutex_init(int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (!omnilock_init(&g_hoomans[i].self))
		{
			philo_mutex_abort(i);
			free(g_hoomans);
			return (FALSE);
		}
	}
	return (TRUE);
}

extern short	philo_init(int count)
{
	int	i;

	g_hoomans = malloc(sizeof(t_philosopher) * count);
	if (!g_hoomans)
		return (FALSE);
	i = -1;
	while (++i < count)
	{
		g_hoomans[i] = (t_philosopher){ 0 };
		g_hoomans[i].uid = i;
		g_hoomans[i].status = phi_dead;
		g_hoomans[i].meals = 0;
		g_hoomans[i].ttaction = ((i + 1) % 2) * g_tteat;
		g_hoomans[i].ttdie = g_ttdie;
		if (g_philocount % 2)
			g_hoomans[i].nextfast = (i + 1) / 2;
		else
			g_hoomans[i].nextfast = -1;
	}
	return (philo_mutex_init(count));
}

extern void		philo_deinit(void)
{
	if (g_hoomans)
	{
		philo_mutex_abort(g_philocount);
		free(g_hoomans);
	}
}
