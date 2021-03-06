/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringgen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:42:14 by abaur             #+#    #+#             */
/*   Updated: 2021/03/06 21:05:54 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

static inline char	gethexdigit(char value)
{
	return (value < 10 ? '0' + value : 'a' + value - 10);
}

extern void			miniitoahex(char dst[9], unsigned int src)
{
	int	i;

	i = 8;
	while (i--)
	{
		dst[i] = gethexdigit(src % 16);
		src /= 16;
	}
	dst[8] = '\0';
}
