/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:20:29 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 02:20:30 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

int	ft_strlen_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_print_matrix(char **matrix, int i)
{
	while (matrix[i])
	{
		ft_printf("%s", matrix[i++]);
		if (matrix[i])
			ft_printf(" ");
	}
}

char	*ft_strdup_chr(char *str, char c)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc(sizeof(char) * (ft_strlen_chr(str, c) + 1));
	if (!dup)
		return (NULL);
	while (str[i] != c && str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

int	check_num(int num)
{
	if (num < 0)
		num = 0;
	else if (num >= 1000)
	{
		ft_printf_fd(2, MSSG_SHLVL_ERR, num + 1);
		num = 1;
	}
	else
		num++;
	return (num);
}

char	*ft_correct_shlvl(char *env)
{
	int		i;
	int		num;
	char	*dup;
	char	*value;

	i = -1;
	dup = malloc(sizeof(char) * (ft_strlen(env) + 1));
	if (!dup)
		return (NULL);
	while (env[++i] != '=')
	{
		dup[i] = env[i];
	}
	dup[i] = '=';
	dup[i + 1] = '\0';
	num = ft_atoi(env + i + 1);
	num = check_num(num);
	value = ft_itoa(num);
	if (!value)
		return (free(dup), NULL);
	dup = ft_strjoin_line(dup, value);
	if (!dup)
		return (free(value), NULL);
	free(value);
	return (dup);
}
