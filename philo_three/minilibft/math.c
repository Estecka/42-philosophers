/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:47:03 by abaur             #+#    #+#             */
/*   Updated: 2021/02/19 16:02:37 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

extern float	clamp(float v, float min, float max)
{
	if (v < min)
		return (min);
	if (max < v)
		return (max);
	return (v);
}

extern float	min(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

extern float	max(float a, float b)
{
	if (a < b)
		return (b);
	else
		return (a);
}
