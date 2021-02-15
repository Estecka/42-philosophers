/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:29:55 by abaur             #+#    #+#             */
/*   Updated: 2021/02/15 14:12:37 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

extern size_t		ministrlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

extern int			miniatoi(const char *arg)
{
	int result;

	result = 0;
	while (*arg)
	{
		result = (result * 10) + *arg - '0';
		arg++;
	}
	return (result);
}

extern short		isnumber(const char *arg)
{
	while (*arg)
	{
		if (*arg < '0' || '9' < *arg)
			return (FALSE);
		arg++;
	}
	return (TRUE);
}

extern __useconds_t	smallest(__useconds_t a, __useconds_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

extern __useconds_t	greatest(__useconds_t a, __useconds_t b)
{
	if (a < b)
		return (b);
	else
		return (a);
}
