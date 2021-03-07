/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:34:46 by abaur             #+#    #+#             */
/*   Updated: 2021/03/07 19:49:45 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

extern noreturn void	throw(int status, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	dprintf(STDERR_FILENO,"\n");
	if (status && status != -1)
		dprintf(STDERR_FILENO, "%3i %s\n", errno, strerror(errno));
	exit(status);
}

extern void				debug(int status, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	if (status && status != -1)
		dprintf(STDERR_FILENO, "%3i %s\n", errno, strerror(errno));
}
