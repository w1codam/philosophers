/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 12:14:34 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/05/24 14:21:46 by jde-groo      ########   odam.nl         */
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
	SLEEPING,
	DEAD
}	t_state;

typedef struct s_philosopher {
	t_uint32		id;
	t_uint32		servings;
	t_uint64		last_meal;
	t_state			state;
	void			*right_fork;
	void			*left_fork;
}	t_philosopher;

typedef struct s_fork {
	pthread_mutex_t	mutex;
	void			*right_philosopher;
	void			*left_philosopher;
}	t_fork;

typedef struct s_rules {
	t_uint64		time_to_die;
	t_uint64		time_to_eat;
	t_uint64		time_to_sleep;
	t_uint64		amount_of_servings;
	bool			min_servings;
}	t_rules;

typedef struct s_table {
	t_int64			n_philosophers;
	pthread_t		*threads;
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

// utility.c
t_uint64	ft_curtime(void);
t_int32		ft_atoi(char *str);
t_int32		ft_strlen(char *str);

// log.c
t_int32		ft_error(char *reason);
void		log_action(t_table *table, t_uint64 timestamp, \
	t_philosopher *philosopher, char *action);

#endif