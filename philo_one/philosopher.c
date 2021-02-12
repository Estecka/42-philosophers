/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:07:46 by abaur             #+#    #+#             */
/*   Updated: 2021/02/12 14:09:20 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "philosopher.h"

#include <pthread.h>
#include <stdlib.h>

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
		g_hoomans[i].status = phi_think;
		g_hoomans[i].meals = 0;
		g_hoomans[i].ttaction = 0;
		g_hoomans[i].ttdie = g_ttdie;
		g_hoomans[i].hands[0] = NULL;
		g_hoomans[i].hands[1] = NULL;
	}
	return (TRUE);
}

extern void		philo_deinit(void)
{
	if (g_hoomans)
		free(g_hoomans);
}
