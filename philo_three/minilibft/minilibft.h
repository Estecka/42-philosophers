/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:22:19 by abaur             #+#    #+#             */
/*   Updated: 2021/03/01 18:41:58 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Pinky promise, it's not the actual libft. -3-
*/

#ifndef MINILIBFT_H
# define MINILIBFT_H

# include <errno.h>
# include <stdnoreturn.h>
# include <unistd.h>

# define TRUE  1
# define FALSE 0

size_t			ministrlen(const char *str);
int				miniatoi(const char *arg);
void			miniitoahex(char dst[5], unsigned int src);
short			isnumber(const char *arg);
useconds_t		smallest(useconds_t a, useconds_t b);
useconds_t		greatest(useconds_t a, useconds_t b);
float			min(float a, float b);
float			max(float a, float b);
float			clamp(float v, float min, float max);

noreturn void	throw(int status, const char *format, ...
) __attribute__((format(printf,2,3)));
void			debug(int status, const char *format, ...
) __attribute__((format(printf,2,3)));

#endif
