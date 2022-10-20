/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 12:39:16 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/10/20 11:34:45 by jde-groo      ########   odam.nl         */
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
		if (table->philosophers[i].servings < table->rules->amount_of_servings)
			return (false);
		i++;
	}
	table->active = false;
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
		difference = curtime - table->philosophers[i].last_meal;
		if (difference > table->rules->time_to_die / 1000)
		{
			table->active = false;
			log_action(table, &table->philosophers[i], "died", true);
			return (true);
		}
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
