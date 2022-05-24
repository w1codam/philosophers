/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 12:14:37 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/05/24 17:28:34 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_table		table;
	t_rules		rules;

	table.rules = &rules;
	if (!parse_rules(argc, argv, &rules))
		ft_error("incorrect argument(s)");
	if (!prepare_table(&table))
		ft_error("failed to prepare table");
	write(1, "success\n", 8);
	return (0);
}
