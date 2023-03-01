/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:43:31 by aelkhali          #+#    #+#             */
/*   Updated: 2023/03/01 17:53:42 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct philos_data
{
	int				num_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				eat_count_limit;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*lock;
}					t_data;

typedef struct philosopher_t
{
	pthread_t		thread;
	int				id;
	int				eat_count;
	int				max_eat_count;
	size_t			tm_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}					t_philo;

/*	Philosophers	*/
void	*routine(void *philo);
void	print_status(t_philo *philo, char *status);

/*	Init Utils		*/
t_data	*init_data(int ac, char **av);
int		check_args_errors(int ac, char **av);
t_philo	*philosophers(int n_philos);
int		init_threads(t_data *data, t_philo *philos);
void	controller(t_data *data, t_philo *philos);

/*	Memory Utils 	*/
int		clean_memory(t_data *data, t_philo *philos);

/*	Global Utils	*/
int		ft_atoi(const char *str);
size_t	get_time(void);

#endif