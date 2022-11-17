/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protected_pthread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 12:57:18 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/11/17 14:44:33 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	p_mutex_init(pthread_mutex_t *mutex)
{
	if (!mutex || pthread_mutex_init(mutex, NULL) != 0)
		return (false);
	return (true);
}

void	p_mutex_lock(pthread_mutex_t *mutex)
{
	if (!mutex)
		return ;
	pthread_mutex_lock(mutex);
}

void	p_mutex_unlock(pthread_mutex_t *mutex)
{
	if (!mutex)
		return ;
	pthread_mutex_unlock(mutex);
}

void	p_join(pthread_t *thread)
{
	if (!thread)
		return ;
	if (pthread_join(*thread, NULL) != 0)
		ft_warn("unable to join thread");
}
