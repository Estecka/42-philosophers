/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:07:46 by abaur             #+#    #+#             */
/*   Updated: 2021/02/17 16:09:25 by abaur            ###   ########.fr       */
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
		pthread_mutex_destroy(&g_hoomans[i].self);
	}
}

static short	philo_mutex_init(int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (0 != pthread_mutex_init(&g_hoomans[i].self, NULL))
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
		g_hoomans[i].uid = i;
		g_hoomans[i].thread = (pthread_t){ 0 };
		g_hoomans[i].status = phi_dead;
		g_hoomans[i].meals = 0;
		g_hoomans[i].ttaction = 0;
		g_hoomans[i].ttdie = g_ttdie;
		g_hoomans[i].hands[0] = NULL;
		g_hoomans[i].hands[1] = NULL;
		g_hoomans[i].self = (pthread_mutex_t){ 0 };
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
