/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoprocess.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:58:54 by abaur             #+#    #+#             */
/*   Updated: 2021/03/04 17:58:43 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOPROCESS_H
# define PHILOPROCESS_H

#include "hermes.h"

/*
** @var unsignedint uid	The unique id of the philsopher.
**
** @var t_hermreceiver sim_abort	Listens for the eventual abortion of the sim
** ulation.
*/

typedef struct s_philoproc	t_philoproc;
struct s_philoproc
{
	unsigned int	uid;

	t_hermreceiver	*sim_abort;
};

#endif