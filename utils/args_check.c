/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:21:19 by aelkhali          #+#    #+#             */
/*   Updated: 2023/03/01 13:49:34 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_args_errors(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (printf("Wrong number of arguments\n"), EXIT_FAILURE);
	while (av[++i])
		if (ft_atoi(av[i]) == 0 || ft_atoi(av[i]) == -1)
			return (printf("Try with > 0 Number\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
