/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_builder.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:09:52 by abaur             #+#    #+#             */
/*   Updated: 2021/03/13 15:16:35 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_BUILDER_H
# define SIMULATION_BUILDER_H

#include "philoprocess.h"
#include "simulation_dashboard.h"
#include "stdnoreturn.h"

/*
** @var t_simdash dashboard
** @var t_philoproc[] philos	Array of philosophers. Mallocated in a single me
** mory block.
** @var t_hermpipe sim_abort
*/

typedef struct s_simbuilder	t_simbuilder;
struct			s_simbuilder
{
	t_simdash	dashboard;
	t_philoproc	*philos;

	t_hermpipe	sim_abort;
	t_hermpipe	fulfillment;
	t_hermpipe	deathes;
};

short			sim_init(t_simbuilder *this);
void			sim_destroy(t_simbuilder *this);
noreturn void	sim_start(t_simbuilder *this);


noreturn void	mutate_demeter(t_simbuilder *this);
noreturn void	mutate_philo(t_simbuilder *this, t_philoproc *philosopher);

#endif