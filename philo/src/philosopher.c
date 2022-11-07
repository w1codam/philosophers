/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 16:52:56 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/11/07 15:32:59 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	p_forks(t_table *table, t_philosopher *philosopher, bool grabbing)
{
	if (!table->active && grabbing)
		return ;
	if (grabbing)
	{
		if (philosopher->id % 2)
		{
			p_mutex_lock(table, &((t_fork *)philosopher->right_fork)->mutex);
			log_action(table, philosopher, "has taken a fork", false);
			if (table->rules->philosophers == 1)
				return ;
			p_mutex_lock(table, &((t_fork *)philosopher->left_fork)->mutex);
			log_action(table, philosopher, "has taken a fork", false);
		}
		else
		{
			p_mutex_lock(table, &((t_fork *)philosopher->left_fork)->mutex);
			log_action(table, philosopher, "has taken a fork", false);
			p_mutex_lock(table, &((t_fork *)philosopher->right_fork)->mutex);
			log_action(table, philosopher, "has taken a fork", false);
		}
		return ;
	}
	p_mutex_unlock(table, &((t_fork *)philosopher->right_fork)->mutex);
	p_mutex_unlock(table, &((t_fork *)philosopher->left_fork)->mutex);
}

static void	p_eat(t_table *table, t_philosopher *philosopher)
{
	if (!table->active)
		return ;
	log_action(table, philosopher, "is eating", false);
	philosopher->state = EATING;
	philosopher->last_meal = ft_curtime();
	ft_sleep(table->rules->time_to_eat / 1000);
	philosopher->servings += 1;
}

static void	p_think(t_table *table, t_philosopher *philosopher)
{
	if (!table->active)
		return ;
	log_action(table, philosopher, "is thinking", false);
	philosopher->state = THINKING;
}

static void	p_sleep(t_table *table, t_philosopher *philosopher)
{
	if (!table->active)
		return ;
	log_action(table, philosopher, "is sleeping", false);
	philosopher->state = SLEEPING;
	ft_sleep(table->rules->time_to_sleep / 1000);
}

void	*philosopher(void *argument)
{
	t_philosopher		*philosopher;
	t_table				*table;

	philosopher = ((t_thread_argument *)argument)->philosopher;
	table = ((t_thread_argument *)argument)->table;
	free((t_thread_argument *)argument);
	while (table->active)
	{
		p_forks(table, philosopher, true);
		if (table->rules->philosophers == 1)
			return (NULL);
		p_eat(table, philosopher);
		p_forks(table, philosopher, false);
		p_sleep(table, philosopher);
		p_think(table, philosopher);
	}
	return (NULL);
}
