/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:56:45 by abaur             #+#    #+#             */
/*   Updated: 2021/02/19 16:02:17 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chronos.h"

#include "minilibft/minilibft.h"

extern __useconds_t		wait_until(__useconds_t target_date)
{
	__useconds_t	current_date;

	while ((current_date = stopwatch_date()) < target_date)
		usleep(smallest(250, target_date - current_date) * g_perfs);
	return (stopwatch_date());
}
