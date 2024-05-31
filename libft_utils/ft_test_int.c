/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:30:09 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/24 14:15:47 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_is_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	return (i);
}

int	ft_test_int(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	i = ft_is_space(str);
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result * sign > (LLONG_MAX - (str[i] - '0')) / 10 || result
			* sign < (LLONG_MIN + (str[i] - '0')) / 10)
			return (-1);
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && ft_is_space(str + i) == 0)
		return (-1);
	return (0);
}
