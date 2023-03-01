/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:21:27 by aelkhali          #+#    #+#             */
/*   Updated: 2023/03/01 15:40:26 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	die_check(t_data *data, t_philo *philos, int i)
{
	if (get_time() - philos[i].tm_last_meal >= data->time_to_die)
		return (printf("%6lu %d %s\n", get_time() - data->start_time, \
			philos[i].id, "died"), EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

void	controller(t_data *data, t_philo *philos)
{
	int	counter;
	int	i;

	counter = 1;
	while (1)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			pthread_mutex_lock(data->lock);
			if (data->eat_count_limit != -1)
			{
				if (philos[i].eat_count == data->eat_count_limit)
				{
					philos[i].eat_count++;
					counter++;
				}
				if (counter == data->num_philos)
					return ;
			}
			if (!die_check(data, philos, i))
				return ;
			pthread_mutex_unlock(data->lock);
		}
	}
}
