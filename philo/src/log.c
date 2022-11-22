/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 15:10:56 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/11/22 14:05:03 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_warn(char *reason)
{
	write(STDERR_FILENO, "warning: ", 9);
	write(STDERR_FILENO, reason, ft_strlen(reason));
	perror("err: ");
}

void	ft_error(t_table *table, char *reason)
{
	pthread_mutex_lock(&table->data_mutex);
	table->active = false;
	pthread_mutex_unlock(&table->data_mutex);
	write(STDERR_FILENO, "error: ", 7);
	write(STDERR_FILENO, reason, ft_strlen(reason));
	wait_threads(table);
	cleanup(table);
	exit(EXIT_FAILURE);
}

void	log_action(t_table *table, t_philosopher *philosopher, \
	char *action, bool force)
{
	pthread_mutex_lock(&table->print_mutex);
	if (safe_read(&table->data_mutex, &table->active) || force)
		printf("%lu %i %s\n", ft_curtime(), philosopher->id, action);
	pthread_mutex_unlock(&table->print_mutex);
}
