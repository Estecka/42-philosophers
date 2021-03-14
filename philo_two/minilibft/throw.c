/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:34:46 by abaur             #+#    #+#             */
/*   Updated: 2021/03/13 19:58:31 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

extern void	throw(int status, const char *format, ...)
{
	printf("%3i %s\n", status, format);
	exit(status);
}

extern void	debug(int status, const char *format, ...)
{
	(void)status;
	(void)format;
	return ;
}
