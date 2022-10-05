/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 12:14:34 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/07/06 16:39:07 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

typedef int					t_int32;
typedef unsigned int		t_uint32;
typedef long				t_int64;
typedef unsigned long		t_uint64;

typedef enum e_state {
	EATING,
	THINKING,
	SLEEPING
}	t_state;

typedef struct s_philosopher {
	t_int32			id;
	t_int32			servings;
	t_int64			last_meal;
	t_state			state;
	void			*right_fork;
	void			*left_fork;
	pthread_t		thread;
}	t_philosopher;

typedef struct s_fork {
	pthread_mutex_t	mutex;
	void			*right_philosopher;
	void			*left_philosopher;
}	t_fork;

typedef struct s_rules {
	t_int32			philosophers;
	t_int64			time_to_die;
	t_int64			time_to_eat;
	t_int64			time_to_sleep;
	t_int32			amount_of_servings;
}	t_rules;

typedef struct s_table {
	pthread_mutex_t	print_mutex;
	t_philosopher	*philosophers;
	t_fork			*forks;
	t_rules			*rules;
	bool			active;
}	t_table;

typedef struct s_thread_argument {
	t_table			*table;
	t_philosopher	*philosopher;
}	t_thread_argument;

// philosopher.c
void		*philosopher(void *argument);

// monitor.c
void		monitor(t_table *table);

// threads.c
bool		start_threads(t_table *table);
void		wait_threads(t_table *table);
void		cleanup(t_table *table);

// setup.c
bool		parse_rules(int argc, char **argv, t_rules *rules);
bool		prepare_table(t_table *table);

// utility.c
t_uint64	ft_curtime(void);
t_int32		ft_atoi(char *str);
t_int32		ft_strlen(char *str);
void		*ft_calloc(size_t count, size_t size);
void		ft_sleep(t_uint64 ms);

// log.c
void		ft_error(t_table *table, char *reason);
void		ft_warn(char *reason);
void		log_action(t_table *table, \
	t_philosopher *philosopher, char *action, bool force);

// protected_pthread.c
void		p_mutex_init(t_table *table, pthread_mutex_t *mutex);
void		p_mutex_lock(t_table *table, pthread_mutex_t *mutex);
void		p_mutex_unlock(t_table *table, pthread_mutex_t *mutex);
void		p_join(pthread_t *thread);

#endif