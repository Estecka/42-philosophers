/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:42:33 by abaur             #+#    #+#             */
/*   Updated: 2021/03/13 18:18:40 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logos.h"

#include "chronos.h"
#include "hermes.h"
#include "omnilock.h"
#include "minilibft/minilibft.h"

#include <stdio.h>

static t_omnilock	g_lock;
static short		g_issilenced;

extern void	logos_init(void)
{
	omnilock_init(&g_lock);
	g_issilenced = FALSE;
}

extern void	logos_deinit(void)
{
	omnilock_deinit(&g_lock);
}

extern void	logos_silence(void)
{
	omnilock_lockup(&g_lock);
	g_issilenced = TRUE;
	omnilock_unlock(&g_lock);
}

extern void	philo_log(suseconds_t ttaction, useconds_t wakedate,
unsigned int philo_uid, const char *message)
{
	(void)ttaction;
	omnilock_lockup(&g_lock);
	if (!g_issilenced)
	{
		printf("%5u %i	%s\n",
			wakedate / MS2USEC, philo_uid, message);
	}
	omnilock_unlock(&g_lock);
}
