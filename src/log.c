/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 15:10:56 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/05/25 14:37:17 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_int32	ft_error(char *reason)
{
	write(STDERR_FILENO, "error: ", 7);
	write(STDERR_FILENO, reason, ft_strlen(reason));
	return (EXIT_FAILURE);
}

void	log_action(t_table *table, t_philosopher *philosopher, char *action)
{
	pthread_mutex_lock(&table->print_mutex);
	if (table->active || ft_strlen(action) == 4)
		printf("%lu %i %s\n", ft_curtime(), philosopher->id, action);
	pthread_mutex_unlock(&table->print_mutex);
}
