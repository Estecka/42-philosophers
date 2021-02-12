/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:22:19 by abaur             #+#    #+#             */
/*   Updated: 2021/02/12 14:39:56 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Pinky promise, it's not the actual libft. -3-
*/

#ifndef MINILIBFT_H
# define MINILIBFT_H

# include <unistd.h>

# define TRUE  1
# define FALSE 0

size_t	ministrlen(const char *str);
int		miniatoi(const char *arg);
short	isnumber(const char *arg);

#endif
