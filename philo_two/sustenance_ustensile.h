/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sustenance_ustensile.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:10:20 by abaur             #+#    #+#             */
/*   Updated: 2021/02/09 15:23:12 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUSTENANCE_USTENSILE_H
# define SUSTENANCE_USTENSILE_H

# include <pthread.h>

/*
** It's a set of forks. The eating kind.
*/

pthread_mutex_t	*g_ustensiles;

short			ustensile_init(int count);
void			ustensile_deinit();

#endif
