/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 14:27:28 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/11/22 14:31:20 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	prepare_philosophers(t_table *table)
{
	int	i;

	table->philosophers = ft_calloc(sizeof(t_philosopher), \
		table->rules->philosophers);
	if (!table->philosophers)
		return (false);
	table->forks = ft_calloc(sizeof(t_fork), \
		table->rules->philosophers);
	if (!table->forks)
	{
		free(table->philosophers);
		table->philosophers = NULL;
		return (false);
	}
	i = 0;
	while (i < table->rules->philosophers)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].last_meal = ft_curtime();
		if (!p_mutex_init(&table->forks[i].mutex))
			return (false);
		i++;
	}
	return (true);
}

static void	seat_philosophers(t_table *table)
{
	int	i;

	i = 0;
	table->philosophers[i].left_fork = \
		&table->forks[table->rules->philosophers - 1];
	while (i < table->rules->philosophers)
	{
		table->philosophers[i].right_fork = &table->forks[i];
		if (i)
			table->philosophers[i].left_fork = &table->forks[i - 1];
		i++;
	}
}

bool	parse_rules(int argc, char **argv, t_rules *rules)
{
	rules->philosophers = 0;
	if (argc < 5 || argc > 6)
		return (false);
	rules->philosophers = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->amount_of_servings = -1;
	if (argc > 5)
		rules->amount_of_servings = ft_atoi(argv[5]);
	if (rules->philosophers > 0 && rules->time_to_die > 0 && \
		rules->time_to_eat > 0 && rules->time_to_sleep > 0 && \
		(argc < 6 || rules->amount_of_servings > 0))
		return (true);
	return (false);
}

bool	prepare_table(t_table *table)
{
	if (!prepare_philosophers(table))
		return (false);
	seat_philosophers(table);
	if (!p_mutex_init(&table->print_mutex) || !p_mutex_init(&table->data_mutex))
		return (false);
	table->active = true;
	return (true);
}
