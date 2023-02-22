/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:43:31 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/22 12:09:46 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

typedef struct philos_data
{
    int				num_philos;
    size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				starting_time;
	int				num_times_to_eat; // optional
	int				philos_finished;
	int				is_alive;
	pthread_mutex_t	*print_lock;
}					t_data;

typedef struct  philosopher_t
{
	pthread_t		thread;
	int				id;
	int				eat_count;
	int				max_eat_count;
	size_t				tm_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}					t_philo;


#endif