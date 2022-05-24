/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 16:52:56 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/05/24 17:30:54 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	p_forks(t_table *table, t_philosopher *philosopher, bool grabbing)
{
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
	log_action(table, philosopher, "is eating");
	philosopher->state = EATING;
	philosopher->last_meal = ft_curtime();
	usleep(table->rules->time_to_eat);
	philosopher->servings += 1;
}

static void	p_think(t_table *table, t_philosopher *philosopher)
{
	log_action(table, philosopher, "is thinking");
	philosopher->state = THINKING;
}

static void	p_sleep(t_table *table, t_philosopher *philosopher)
{
	log_action(table, philosopher, "is sleeping");
	philosopher->state = SLEEPING;
	usleep(table->rules->time_to_sleep);
}

void	*philosopher(void *argument)
{
	t_thread_argument	*arg;

	arg = (t_thread_argument *)argument;
	while (arg->table->active)
	{
		p_forks(arg->table, arg->philosopher, true);
		p_eat(arg->table, arg->philosopher);
		p_forks(arg->table, arg->philosopher, false);
		p_sleep(arg->table, arg->philosopher);
		p_think(arg->table, arg->philosopher);
	}
	return (NULL);
}
