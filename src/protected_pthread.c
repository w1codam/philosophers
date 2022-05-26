/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protected_pthread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 12:57:18 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/05/26 14:34:41 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	p_mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		ft_error("unable to initialize mutex");
}

void	p_mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		ft_error("unable to lock mutex");
}

void	p_mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
		ft_error("unable to unlock mutex");
}
