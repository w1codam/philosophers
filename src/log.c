/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 15:10:56 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/07/05 16:46:14 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_warn(char *reason)
{
	write(STDERR_FILENO, "warning: ", 9);
	write(STDERR_FILENO, reason, ft_strlen(reason));
}

void	ft_error(t_table *table, char *reason)
{
	table->active = false;
	write(STDERR_FILENO, "error: ", 7);
	write(STDERR_FILENO, reason, ft_strlen(reason));
	wait_threads(table);
	cleanup(table);
	exit(EXIT_FAILURE);
}

void	log_action(t_table *table, t_philosopher *philosopher, \
	char *action, bool force)
{
	p_mutex_lock(table, &table->print_mutex);
	if (table->active || force)
		printf("%lu %i %s\n", ft_curtime(), philosopher->id, action);
	p_mutex_unlock(table, &table->print_mutex);
}
