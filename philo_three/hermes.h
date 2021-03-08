/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hermes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:06:52 by abaur             #+#    #+#             */
/*   Updated: 2021/03/08 17:51:03 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Semaphore-based unary communication between processes.
*/

#ifndef HERMES_H
# define HERMES_H

# include "omnilock.h"

# include <pthread.h>
# include <semaphore.h>

/*
** @var t_omnilocks locks	The semaphore used to send the event.
*/

typedef struct s_hermsender		t_hermsender;
struct			s_hermsender
{
	t_omnilock		locks;
};

/*
** @var unsigned int autostop	The maximum amount of events that is expected to
**  be received. The receiver thread will automatically shut down when this limi
** t is reached.
** @var pthread_t thread	The id of the receiver thread.
** @var sem_t* semaphore	The semaphore being listened to.
** @var unsigned int		The amount of unacknowlegded events received through
**  this semaphore.
** @var void*(*)(void*) reaction	A function to execute whenever an event is r
** eceived.
** @var void* reaction_arg	An argument to be passed to the reaction function.
*/

typedef struct s_hermreceiver	t_hermreceiver;
struct			s_hermreceiver
{
	unsigned int		autostop;
	pthread_t			thread;
	sem_t				*semaphore;
	unsigned int		value;
	void				*(*reaction)(t_hermreceiver*, void*);
	void				*reaction_arg;
};

/*
** @var unsigned int duplicatas	The amount of receivers for this pipe.
** @var t_hermsender	The sender for this pipe.
** @var t_hermreceiver receiver	The receiver for this pipe.
*/

typedef struct s_hermpipe		t_hermpipe;
struct			s_hermpipe
{
	t_hermsender	sender;
	t_hermreceiver	receivers;
};

/*
** Initializes a set of sender and receivers.
** @param t_hermpipe* this	The hermpipe to store the sender and receiver.
** @param unsigned int dups	The amount of receivers for this pipe.
** @param unsigned int max	The maximum amount of events that should be sent thr
** ough the pipe.
*/

void			hermes_init(t_hermpipe *this, unsigned int max);

/*
** Destroys the semaphore for this sender.
*/

void			hermsender_destroy(t_hermsender *this);

/*
** Stops the receiver thread.
** The semaphore is left untouched; it is considered the sender's duty to destro
** y the semaphores.
*/

void			hermreceiver_destroy(t_hermreceiver *this);

/*
** Starts listening to the semaphore.
*/

short			hermreceiver_start(t_hermreceiver *this);
void			hermreceiver_stop(t_hermreceiver *this);

/*
** Broadcasts datas to all receivers.
** @param t_hermsender* this	Where to send the message.
** @param unsigned int amount	The amount of events to be sent to each receiver
** .
*/

void			hermes_send(t_hermsender *this, unsigned int amount);

unsigned int	hermes_receive(t_hermreceiver *this);

#endif
