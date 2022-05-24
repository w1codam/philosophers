/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 14:27:28 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/05/24 14:49:46 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	parse_rules(int argc, char **argv, t_rules *rules)
{
	if (argc < 5 || argc > 6)
		return (false);
	rules->philosophers = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->amount_of_servings = -1;
	if (argc > 5)
		rules->amount_of_servings = ft_atoi(argv[5]);
	if (rules->philosophers > 0 && rules->time_to_die >= 0 && \
		rules->time_to_eat >= 0 && rules->time_to_sleep >= 0 && \
		(argc < 6 || rules->amount_of_servings >= 0))
		return (true);
	return (false);
}
