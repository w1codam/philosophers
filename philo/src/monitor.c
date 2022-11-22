/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 12:39:16 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/11/22 14:30:46 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	check_servings(t_table *table)
{
	int	i;

	if (table->rules->amount_of_servings < 0)
		return (false);
	i = 0;
	while (i < table->rules->philosophers)
	{
		pthread_mutex_lock(&table->data_mutex);
		if (table->philosophers[i].servings < table->rules->amount_of_servings)
		{
			pthread_mutex_unlock(&table->data_mutex);
			return (false);
		}
		pthread_mutex_unlock(&table->data_mutex);
		i++;
	}
	pthread_mutex_lock(&table->data_mutex);
	table->active = false;
	pthread_mutex_unlock(&table->data_mutex);
	return (true);
}

static bool	check_death(t_table *table)
{
	int		i;
	t_int64	difference;
	t_int64	curtime;

	i = 0;
	curtime = ft_curtime();
	while (i < table->rules->philosophers)
	{
		pthread_mutex_lock(&table->data_mutex);
		difference = curtime - table->philosophers[i].last_meal;
		if (difference > table->rules->time_to_die)
		{
			pthread_mutex_unlock(&table->data_mutex);
			pthread_mutex_lock(&table->data_mutex);
			table->active = false;
			pthread_mutex_unlock(&table->data_mutex);
			log_action(table, &table->philosophers[i], "died", true);
			return (true);
		}
		pthread_mutex_unlock(&table->data_mutex);
		i++;
	}
	return (false);
}

void	monitor(t_table *table)
{
	while (true)
	{
		if (check_servings(table))
			break ;
		if (check_death(table))
			break ;
		usleep(10);
	}
}
