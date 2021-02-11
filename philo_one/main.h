/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:14:10 by abaur             #+#    #+#             */
/*   Updated: 2021/02/11 16:03:20 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>

# define FALSE 0
# define TRUE 1

unsigned int	g_philocount;
signed int		g_eatgoal;
__useconds_t	g_ttdie;
__useconds_t	g_tteat;
__useconds_t	g_ttsleep;

#endif
