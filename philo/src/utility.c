/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 15:07:54 by jde-groo      #+#    #+#                 */
/*   Updated: 2022/05/25 16:57:40 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_uint64	ft_curtime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_int32	ft_atoi(char *str)
{
	t_int32	result;
	t_int32	negative;
	t_int32	index;

	negative = 1;
	result = 0;
	index = 0;
	while (str[index] <= ' ' && str[index] != '\e' && str[index] != '\0')
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			negative = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + (str[index] - '0');
		index++;
	}
	return (result * negative);
}

t_int32	ft_strlen(char *str)
{
	t_int32	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	t_uint64	i;
	void		*res;

	i = 0;
	res = malloc(count * size);
	if (!res)
		return (NULL);
	while (i < count * size)
	{
		((char *)res)[i] = 0;
		i++;
	}
	return (res);
}

void	ft_sleep(t_uint64 ms)
{
	t_uint64	cur;

	cur = ft_curtime();
	while (ft_curtime() - cur < ms)
		usleep(100);
}
