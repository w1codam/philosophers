/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 12:52:09 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/07/05 15:27:12 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	start_threads(t_table *table)
{
	int					i;
	t_thread_argument	*arg;

	i = 0;
	while (i < table->rules->philosophers)
	{
		arg = malloc(sizeof(t_thread_argument));
		if (!arg)
			return (false);
		arg->table = table;
		arg->philosopher = &table->philosophers[i];
		if (pthread_create(&table->philosophers[i].thread, NULL, \
			philosopher, (void *)arg) != 0)
			return (false);
		i++;
	}
	return (true);
}

void	wait_threads(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->rules->philosophers && table->philosophers)
	{
		pthread_mutex_unlock(&((t_fork *)table->philosophers[i] \
			.right_fork)->mutex);
		pthread_mutex_unlock(&((t_fork *)table->philosophers[i] \
			.left_fork)->mutex);
		pthread_mutex_unlock(&((t_fork *)table->philosophers[i] \
			.right_fork)->mutex);
		pthread_mutex_unlock(&((t_fork *)table->philosophers[i] \
			.left_fork)->mutex);
		p_join(table, &table->philosophers[i].thread);
		i++;
	}
}

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->rules->philosophers && table->forks)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
	free(table->forks);
	free(table->philosophers);
}
