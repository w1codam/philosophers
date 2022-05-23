/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 12:14:34 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/05/23 13:02:55 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>		// printf
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>

typedef enum e_state {
	eating,
	thinking,
	sleeping
}	t_state;

typedef struct s_philosopher {
	int		id;
	t_state	state;
	void	*right_fork;
	void	*left_fork;
}	t_philosopher;

typedef struct s_fork {
	pthread_mutex_t	*mutex;
	void			*right_philosopher;
	void			*left_philosopher;
}	t_fork;

typedef struct s_table {
	pthread_mutex_t	*death_mutex;
	t_philosopher	*philosophers;
	t_philosopher	*dead_philosopher;
}	t_table;

typedef struct s_thread_argument {
	t_table			*table;
	t_philosopher	*philosopher;
}	t_thread_argument;

#endif