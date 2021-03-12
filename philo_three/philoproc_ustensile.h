/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoproc_ustensile.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:41:41 by abaur             #+#    #+#             */
/*   Updated: 2021/03/12 17:08:17 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_USTENSILE_H
# define PHILOSOPHER_USTENSILE_H

# include "philoprocess.h"

void	philo_grab_ustensiles(t_philoproc *this);
void	philo_drop_ustensiles(t_philoproc *this);

#endif
