/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:26:58 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 02:26:59 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_get_hex(unsigned long nb, int test)
{
	char	*base;
	int		i;

	i = 0;
	base = "0123456789abcdef";
	if (nb >= 16 && test != -1 && i != -1)
	{
		test = ft_get_hex(nb / 16, test);
		i = ft_test_write(test, i);
		if (i == -1)
			return (i);
		test = ft_get_hex(nb % 16, test);
		i = ft_test_write(test, i);
		if (i == -1)
			return (i);
	}
	else
	{
		test = ft_printchar(base[nb]);
		i = ft_test_write(test, i);
	}
	return (i);
}

int	ft_printundhex(unsigned int nb, int test)
{
	char	*base;
	int		i;

	i = 0;
	base = "0123456789abcdef";
	if (nb >= 16 && test != -1 && i != -1)
	{
		test = ft_printundhex(nb / 16, test);
		i = ft_test_write(test, i);
		if (i == -1)
			return (i);
		test = ft_printundhex(nb % 16, test);
		i = ft_test_write(test, i);
		if (i == -1)
			return (i);
	}
	else
	{
		test = ft_printchar(base[nb]);
		i = ft_test_write(test, i);
	}
	return (i);
}

int	ft_printuphex(unsigned int nb, int test)
{
	char	*base;
	int		i;

	i = 0;
	base = "0123456789ABCDEF";
	if (nb >= 16 && test != -1 && i != -1)
	{
		test = ft_printuphex(nb / 16, test);
		i = ft_test_write(test, i);
		if (i == -1)
			return (i);
		test = ft_printuphex(nb % 16, test);
		i = ft_test_write(test, i);
		if (i == -1)
			return (i);
	}
	else
	{
		test = ft_printchar(base[nb]);
		i = ft_test_write(test, i);
	}
	return (i);
}

int	ft_printpnt(unsigned long pointer)
{
	int	count;
	int	aux;

	aux = 0;
	count = ft_printstr("0x");
	if (count == -1)
		return (count);
	aux = ft_get_hex(pointer, 0);
	if (aux != -1)
		count += aux;
	else
		return (aux);
	return (count);
}
