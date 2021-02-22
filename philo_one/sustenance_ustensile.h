/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sustenance_ustensile.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:10:20 by abaur             #+#    #+#             */
/*   Updated: 2021/02/21 15:07:41 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUSTENANCE_USTENSILE_H
# define SUSTENANCE_USTENSILE_H

# include <pthread.h>
# include <semaphore.h>

/*
** It's a set of forks. The eating kind.
*/

# ifdef philo_one

pthread_mutex_t	*g_ustensiles;

# else

sem_t			*g_ustensiles;

# endif

short			ustensile_init(int count);
void			ustensile_deinit();

#endif
