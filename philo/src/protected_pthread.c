/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protected_pthread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/26 12:57:18 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/11/22 14:06:08 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	p_mutex_init(pthread_mutex_t *mutex)
{
	if (!mutex || pthread_mutex_init(mutex, NULL) != 0)
		return (false);
	return (true);
}

void	p_join(pthread_t *thread)
{
	if (!thread)
		return ;
	if (pthread_join(*thread, NULL) != 0)
		ft_warn("unable to join thread");
}
