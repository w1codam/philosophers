/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 12:14:37 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/11/24 14:32:48 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_table		table;
	t_rules		rules;

	table.philosophers = NULL;
	table.forks = NULL;
	table.rules = &rules;
	if (!parse_rules(argc, argv, &rules))
		return (ft_error(&table, "incorrect argument(s)"));
	if (!prepare_table(&table))
		return (ft_error(&table, "failed to prepare table"));
	if (!start_threads(&table))
		return (ft_error(&table, "failed to start threads"));
	monitor(&table);
	wait_threads(&table);
	cleanup(&table);
}
