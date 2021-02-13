/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:57:49 by abaur             #+#    #+#             */
/*   Updated: 2021/02/13 14:55:12 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

typedef enum e_sim_status	t_sim_status;
enum	e_sim_status
{
	sim_stopped = 0,
	sim_playing = 1,
};

t_sim_status	g_sim_status;

/*
** Starts the simulation, and plays it until a philosopher dies, or all philosop
** hers have finished eating.
*/

short	simulation_main(void);

#endif
