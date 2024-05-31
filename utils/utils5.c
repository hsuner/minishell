/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:20:49 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/24 14:20:45 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	quote_len1(char *data)
{
	int	j;
	int	i;
	int	a;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '\"' || data[i] == '\'')
		{
			j++;
			a = data[i++];
			while (data[i] && data[i] != a)
			{
				i++;
			}
			if (!data[i])
				break ;
			j++;
		}
		i++;
	}
	return (j);
}

int	quote_check(char *data, int i)
{
	int	x;

	x = 0;
	x = quote_len1(data);
	if (x % 2 != 0)
	{
		if (i == 1)
			printf("minishell: quote error\n");
		return (0);
	}
	return (1);
}

int	ignore_quote(char const *cmd, int i)
{
	if (cmd[i] == '\"')
	{
		i++;
		while (cmd[i] != '\"')
			i++;
	}
	else if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] != '\'')
			i++;
	}
	return (i);
}

int	ft_strcmp_env2(char *env, char *str)
{
	int	i;

	i = 0;
	while (env[i] != '=' && str[i] != '\0')
	{
		if (env[i] == '\0' && str[i])
			return (0);
		if (env[i] != str[i])
			return (env[i] - str[i]);
		i++;
	}
	if (env[i] == '=' && str[i] == '\0')
		return (0);
	return (env[i] - str[i]);
}

int	ft_only_dollar(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '$')
			i++;
		else
			i++;
	}
	return (i);
}
