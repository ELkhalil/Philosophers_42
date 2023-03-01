/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:23:21 by aelkhali          #+#    #+#             */
/*   Updated: 2023/03/01 13:36:52 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	init_mutexes(t_data *data)
{
	if (!data)
		return (EXIT_FAILURE);
	data->lock = malloc (sizeof(pthread_mutex_t));
	data->print_lock = malloc (sizeof(pthread_mutex_t));
	if (!data->lock || !data->print_lock)
		return (EXIT_FAILURE);
	pthread_mutex_init(data->lock, NULL);
	pthread_mutex_init(data->print_lock, NULL);
	data->start_time = get_time();
	return (EXIT_SUCCESS);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->eat_count_limit = -1;
	if (ac == 6)
		data->eat_count_limit = ft_atoi(av[5]);
	if (init_mutexes(data))
		return (free(data), NULL);
	return (data);
}

pthread_mutex_t	*forks_data(int n_philos)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = malloc (sizeof(pthread_mutex_t) * n_philos);
	if (!forks)
		return (NULL);
	while (++i < n_philos)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}

t_philo	*philosophers(int n_philos)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = forks_data(n_philos);
	philos = malloc (sizeof(t_philo) * n_philos);
	if (!philos || !forks)
		return (NULL);
	while (++i < n_philos)
	{
		memset(&philos[i], 0, sizeof(t_philo));
		philos[i].id = i + 1;
		philos[i].left_fork = forks + i;
		philos[i].right_fork = forks + i + 1;
		if (i == n_philos - 1)
			philos[i].right_fork = forks;
	}
	return (philos);
}

int	init_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		philos[i].data = data;
		philos[i].tm_last_meal = get_time();
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		pthread_detach(philos[i].thread);
	}
	return (EXIT_SUCCESS);
}
