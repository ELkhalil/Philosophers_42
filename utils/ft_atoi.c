/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:03:05 by aelkhali          #+#    #+#             */
/*   Updated: 2023/02/28 18:20:16 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	ft_isdigit(int c)
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
