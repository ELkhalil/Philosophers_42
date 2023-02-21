/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:43:36 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/21 18:10:09 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_error(char *msg, t_data *data)
{
	if (msg)
		printf("%s\n", msg);
	if (data)
		free(data);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		i;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14) || !str[0])
		return (-1);
	if (str[i] == '-')
		sign *= -1;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
		i++;
	while (ft_isdigit(str[i]))
	{
		result = (result * 10) + (str[i] - '0');
		if (result > INT32_MAX && result * sign != INT32_MIN)
			return (-1);
		i++;
	}
	if (str[i] || sign == -1)
		return (-1);
	return (result * sign);
}

void	print_status(t_philo *philosopher, char *status)
{
	struct timeval	current_time;
	int				time_ms;

	gettimeofday(&current_time, NULL);
	time_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	pthread_mutex_lock(philosopher->data->print_lock);
	printf("%d %d %s\n", time_ms, philosopher->id, status);
	pthread_mutex_unlock(philosopher->data->print_lock);
}

int	check_init_data(t_data *data, int ac, char **av)
{
	int				i;
	struct 			timeval	current_time;

	if (ac < 5 || ac > 6)
	{
		print_error("Wrong number of arguments", data);
		return(EXIT_FAILURE);
	}
	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) == -1)
			return (print_error("Wrong type of arguments", data), EXIT_FAILURE);
		else if (!ft_atoi(av[i]))
			return (EXIT_FAILURE);
	}
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->num_times_to_eat = -1;
	if (ac == 6)
		data->num_times_to_eat = ft_atoi(av[5]);
	data->print_lock = malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init(data->print_lock, NULL);
	gettimeofday(&current_time, NULL);
	data->starting_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (EXIT_SUCCESS);
}

void	*routine(void *philo)
{
	t_philo	*philosopher;
	struct timeval	current_time;

	philosopher = philo;
	while (1)
	{
		pthread_mutex_lock(philosopher->left_fork);
		pthread_mutex_lock(philosopher->right_fork);
		print_status(philosopher, "has taken a fork");
		print_status(philosopher, "has taken a fork");
		print_status(philosopher, "is eating");
		usleep(philosopher->data->time_to_eat * 1000);
		philosopher->eat_count++;
		gettimeofday(&current_time, NULL);
		philosopher->tm_last_meal = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000) - philosopher->data->starting_time;
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
		print_status(philosopher, "is sleeping");
		usleep(philosopher->data->time_to_sleep * 1000);
		print_status(philosopher, "is thinking");
	}
}

int	main(int ac, char **av)
{
	pthread_mutex_t *forks;
	t_philo			*philos;
	t_data			*data;
	int				i;
	int				tmp;
	int				flag;

	data = malloc(sizeof(t_data));
	if (check_init_data(data, ac, av))
		return (EXIT_FAILURE);
	philos = malloc(sizeof(t_philo) * data->num_philos);
	forks = malloc (sizeof(pthread_mutex_t) * data->num_philos);
	if (!philos || !forks)
		return (print_error("Allcoation Error", data), EXIT_FAILURE);
	// init mutexes
	i = -1;
	while(++i < data->num_philos)
		pthread_mutex_init(&forks[i], NULL);
	// init philosophers structs and locks
	i = -1;
	while (++i < data->num_philos)
	{
		memset(&philos[i], 0, sizeof(t_philo));
		philos[i].id = i;
		philos[i].left_fork = forks + i;
		philos[i].right_fork = forks + i + 1;
		if (i == data->num_philos - 1)
			philos[i].right_fork = forks;
	}
	
	//threads creation for philosophers
	i = -1;
	while (++i < data->num_philos)
	{
		philos[i].data = data;
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
	}
	tmp = 0;
	flag = 1;
	while (flag)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			if (data->num_times_to_eat != -1)
			{
				if(philos[i].eat_count >= data->num_times_to_eat)
					tmp ++;
				if (tmp == data->num_philos)
				{
					flag = 0;
					break;
				}
					
			}
			if (philos[i].tm_last_meal > data->time_to_die)
			{
				print_status(&philos[i], "died");
				flag = 0;
				break;
			}
		}
	}
	// clean up the program
	return (EXIT_SUCCESS);
}
