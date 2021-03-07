/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_dashboard.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:05:49 by abaur             #+#    #+#             */
/*   Updated: 2021/03/07 18:33:28 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_DASHBOARD_H
# define SIMULATION_DASHBOARD_H

#include "hermes.h"

typedef struct s_simdash	t_simdash;
struct s_simdash
{
	pid_t			*processes;
	t_hermsender	sim_abort;
	t_hermreceiver	fulfillment;
};

#endif