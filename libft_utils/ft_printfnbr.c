/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:28:31 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 02:28:32 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

int	ft_printnbr(int n)
{
	char	*num;
	int		writed;

	num = ft_itoa(n);
	if (!num)
		return (-1);
	writed = ft_printstr(num);
	free(num);
	return (writed);
}

int	ft_printunnbr(unsigned int num, int test)
{
	int	i;

	i = 0;
	if (num >= 10 && test != -1 && i != -1)
	{
		test = ft_printunnbr(num / 10, test);
		i = ft_test_write(test, i);
		if (i == -1)
			return (i);
		test = ft_printunnbr(num % 10, test);
		i = ft_test_write(test, i);
		if (i == -1)
			return (i);
	}
	else
	{
		test = ft_printchar(num + '0');
		i = ft_test_write(test, i);
	}
	return (i);
}
