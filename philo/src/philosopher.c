/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 16:52:56 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/11/22 14:31:15 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	p_forks(t_table *table, t_philosopher *philosopher, bool grabbing)
{
	if (!safe_read(&table->data_mutex, &table->active) && grabbing)
		return ;
	if (grabbing)
	{
		if (philosopher->id % 2)
		{
			pthread_mutex_lock(&((t_fork *)philosopher->right_fork)->mutex);
			log_action(table, philosopher, "has taken a fork", false);
			if (table->rules->philosophers == 1)
				return ;
			pthread_mutex_lock(&((t_fork *)philosopher->left_fork)->mutex);
			log_action(table, philosopher, "has taken a fork", false);
		}
		else
		{
			pthread_mutex_lock(&((t_fork *)philosopher->left_fork)->mutex);
			log_action(table, philosopher, "has taken a fork", false);
			pthread_mutex_lock(&((t_fork *)philosopher->right_fork)->mutex);
			log_action(table, philosopher, "has taken a fork", false);
		}
		return ;
	}
	pthread_mutex_unlock(&((t_fork *)philosopher->right_fork)->mutex);
	pthread_mutex_unlock(&((t_fork *)philosopher->left_fork)->mutex);
}

static void	p_eat(t_table *table, t_philosopher *philosopher)
{
	if (!safe_read(&table->data_mutex, &table->active))
		return ;
	log_action(table, philosopher, "is eating", false);
	pthread_mutex_lock(&table->data_mutex);
	philosopher->last_meal = ft_curtime();
	pthread_mutex_unlock(&table->data_mutex);
	ft_sleep(table->rules->time_to_eat);
	pthread_mutex_lock(&table->data_mutex);
	philosopher->servings += 1;
	pthread_mutex_unlock(&table->data_mutex);
}

static void	p_think(t_table *table, t_philosopher *philosopher)
{
	if (!safe_read(&table->data_mutex, &table->active))
		return ;
	log_action(table, philosopher, "is thinking", false);
}

static void	p_sleep(t_table *table, t_philosopher *philosopher)
{
	if (!safe_read(&table->data_mutex, &table->active))
		return ;
	log_action(table, philosopher, "is sleeping", false);
	ft_sleep(table->rules->time_to_sleep);
}

void	*philosopher(void *argument)
{
	t_philosopher		*philosopher;
	t_table				*table;

	philosopher = ((t_thread_argument *)argument)->philosopher;
	table = ((t_thread_argument *)argument)->table;
	free((t_thread_argument *)argument);
	while (safe_read(&table->data_mutex, &table->active))
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
