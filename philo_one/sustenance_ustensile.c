/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sustenance_ustensile.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:09:41 by abaur             #+#    #+#             */
/*   Updated: 2021/02/09 15:41:52 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "sustenance_ustensile.h"

# include <stdlib.h>

static void		ustensile_abort(int count)
{
	int	i;

	i = -1;
	while(++i < count)
		pthread_mutex_destroy(&g_ustensiles[i]);
	free(g_ustensiles);
}

extern void	ustensile_deinit()
{
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
