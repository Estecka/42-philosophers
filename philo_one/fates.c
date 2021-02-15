/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fates.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:48:38 by abaur             #+#    #+#             */
/*   Updated: 2021/02/15 13:56:55 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fated_list_of_minor_prophecies.h"

#include "chronos.h"
#include "main.h"

extern __useconds_t	philo_starve_date(t_philosopher *this)
{
	if (this->status == phi_eating && this->ttaction < this->ttdie)
		return (this->ttaction + g_ttdie);
	else
		return (this->ttdie);
}

extern __useconds_t	philo_stuffed_date(t_philosopher *this)
{
	__useconds_t	result;

	if (g_eatgoal < 0)
		return (-1);
	else if (this->meals <= (unsigned int)g_eatgoal)
		return (0);
	result = (g_tteat + g_ttsleep) * (g_eatgoal - this->meals - 1);
	if (this->status == phi_eating)
		result += this->ttaction;
	else if (this->status == phi_sleeping)
		result += this->ttaction + g_tteat;
	else if (this->status == phi_thinking)
		result += stopwatch_date() + g_tteat;
	else
		return (-1);
	return (result);
}
