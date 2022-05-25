/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 16:52:56 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/05/25 17:01:37 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	p_forks(t_table *table, t_philosopher *philosopher, bool grabbing)
{
	if (!table->active)
		return ;
	if (grabbing)
	{
		pthread_mutex_lock(&((t_fork *)philosopher->right_fork)->mutex);
		log_action(table, philosopher, "has taken a fork");
		pthread_mutex_lock(&((t_fork *)philosopher->left_fork)->mutex);
		log_action(table, philosopher, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&((t_fork *)philosopher->right_fork)->mutex);
		pthread_mutex_unlock(&((t_fork *)philosopher->left_fork)->mutex);
	}
}

static void	p_eat(t_table *table, t_philosopher *philosopher)
{
	if (!table->active)
		return ;
	log_action(table, philosopher, "is eating");
	philosopher->state = EATING;
	philosopher->last_meal = ft_curtime();
	ft_sleep(table->rules->time_to_eat / 1000);
	philosopher->servings += 1;
}

static void	p_think(t_table *table, t_philosopher *philosopher)
{
	if (!table->active)
		return ;
	log_action(table, philosopher, "is thinking");
	philosopher->state = THINKING;
}

static void	p_sleep(t_table *table, t_philosopher *philosopher)
{
	if (!table->active)
		return ;
	log_action(table, philosopher, "is sleeping");
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
	ft_sleep(philosopher->id);
	while (table->active)
	{
		p_forks(table, philosopher, true);
		p_eat(table, philosopher);
		p_forks(table, philosopher, false);
		p_sleep(table, philosopher);
		p_think(table, philosopher);
	}
	return (NULL);
}
