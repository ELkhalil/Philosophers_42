/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:17:59 by aelkhali          #+#    #+#             */
/*   Updated: 2023/03/01 17:57:11 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_usleep(size_t time)
{
	size_t	tmp_time;

	tmp_time = get_time();
	usleep(time - 10000);
	while (1)
	{
		if (get_time() - tmp_time >= time / 1000)
			break ;
		usleep(200);
	}
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->data->print_lock);
	printf("%6lu %d %s\n", get_time() - philo->data->start_time, \
		philo->id, status);
	pthread_mutex_unlock(philo->data->print_lock);
}

void	*routine(void *philo)
{
	t_philo	*philosopher;

	philosopher = philo;
	if (philosopher->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(philosopher->left_fork);
		print_status(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->right_fork);
		print_status(philosopher, "has taken a fork");
		print_status(philosopher, "is eating");
		ft_usleep(philosopher->data->time_to_eat * 1000);
		pthread_mutex_lock(philosopher->data->lock);
		philosopher->eat_count++;
		philosopher->tm_last_meal = get_time();
		pthread_mutex_unlock(philosopher->data->lock);
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
		print_status(philosopher, "is sleeping");
		ft_usleep(philosopher->data->time_to_sleep * 1000);
		print_status(philosopher, "is thinking");
	}
}
