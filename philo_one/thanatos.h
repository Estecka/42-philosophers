/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thanatos.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:23:29 by abaur             #+#    #+#             */
/*   Updated: 2021/02/15 19:06:40 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Death Incarnate watches over the mortals, ready to take them away as soon as
**  their time has come.
*/

#ifndef THANATOS_H
# define THANATOS_H

# include <unistd.h>

/*
** Report about the health of a philosopher.
** @var bool isDead	Whether the mortal has trespassed.
** @var bool isFulfilled	Whether the philosopher has fulfilled their lifelong
**  dream of eating an entire bowl of spaghettis.
** @var
*/

typedef struct s_philo_medcheck	t_philo_medcheck;
struct				s_philo_medcheck
{
	short			isdead;
	short			isfulfilled;
	__useconds_t	next_check;
};

extern __useconds_t	watch_over_mortals(void);

#endif
