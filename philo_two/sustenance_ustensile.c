/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sustenance_ustensile.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:09:41 by abaur             #+#    #+#             */
/*   Updated: 2021/02/21 21:24:36 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "sustenance_ustensile.h"
#include "minilibft/minilibft.h"

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifdef philo_one

static void		ustensile_abort(int count)
{
	int	i;

	i = -1;
	while (++i < count)
		pthread_mutex_destroy(&g_ustensiles[i]);
	free(g_ustensiles);
}

extern void		ustensile_deinit(void)
{
	if (g_ustensiles)
		ustensile_abort(g_philocount);
}

extern short	ustensile_init(int count)
{
	int	i;
	int	status;

	g_ustensiles = malloc(sizeof(pthread_mutex_t) * count);
	if (!g_ustensiles)
		return (FALSE);
	i = -1;
	while (++i < count)
	{
		status = pthread_mutex_init(&g_ustensiles[i], NULL);
		if (status)
		{
			return (FALSE);
		}
	}
	return (TRUE);
}

#else

extern void		ustensile_deinit(void)
{
	sem_unlink("Instruments of Sustenance");
	g_ustensiles = NULL;
}

extern short	ustensile_init(int count)
{
	g_ustensiles = sem_open("Instruments of Sustenance",
		O_CREAT | O_EXCL,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,
		count);
	if (g_ustensiles == SEM_FAILED)
		return (FALSE);
	else
		return (TRUE);
}

#endif
