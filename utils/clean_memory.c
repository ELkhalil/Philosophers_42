/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:52:17 by aelkhali          #+#    #+#             */
/*   Updated: 2023/03/01 17:52:38 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	clean_memory(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	if (!data || !philos)
		return (EXIT_FAILURE);
	while (++i < data->num_philos)
	{
		pthread_mutex_destroy(philos[i].left_fork);
		pthread_mutex_destroy(philos[i].right_fork);
		if (i < data->num_philos - 1)
			break ;
	}
	pthread_mutex_destroy(data->print_lock);
	pthread_mutex_destroy(data->lock);
	if (data->lock)
		free(data->lock);
	if (data->print_lock)
		free(data->print_lock);
	if (philos[0].left_fork)
		free(philos[0].left_fork);
	if (philos)
		free(philos);
	if (data)
		free(data);
	return (EXIT_SUCCESS);
}
