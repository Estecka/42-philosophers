/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_dashboard.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:05:49 by abaur             #+#    #+#             */
/*   Updated: 2021/03/06 15:26:50 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_DASHBOARD_H
# define SIMULATION_DASHBOARD_H

#include "hermes.h"

typedef struct s_simdash	t_simdash;
struct s_simdash
{
	pid_t			*processes;
	t_hermsender	*sim_abort;
};

#endif