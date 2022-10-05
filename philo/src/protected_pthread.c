/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protected_pthread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 12:57:18 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/07/06 16:39:02 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	p_mutex_init(t_table *table, pthread_mutex_t *mutex)
{
	if (!mutex)
		return ;
	if (pthread_mutex_init(mutex, NULL) != 0)
		ft_error(table, "unable to initialize mutex");
}

void	p_mutex_lock(t_table *table, pthread_mutex_t *mutex)
{
	if (!mutex)
		return ;
	if (pthread_mutex_lock(mutex) != 0)
		ft_error(table, "unable to lock mutex");
}

void	p_mutex_unlock(t_table *table, pthread_mutex_t *mutex)
{
	if (!mutex)
		return ;
	if (pthread_mutex_unlock(mutex) != 0)
		ft_error(table, "unable to unlock mutex");
}

void	p_join(pthread_t *thread)
{
	if (!thread)
		return ;
	if (pthread_join(*thread, NULL) != 0)
		ft_warn("unable to join thread");
}
