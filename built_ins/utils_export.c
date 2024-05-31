/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:25:52 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/23 20:11:06 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

char	*ft_strdup_join(char *str)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc(sizeof(char) * ft_strlen(str));
	if (!dup)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != '+')
			dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin_export(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)));
	if (!str)
		return (NULL);
	while (s1[i] != C_TWO_QUOTE || flag == 0)
	{
		if (s1[i] == C_TWO_QUOTE)
			flag = 1;
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '=')
		j++;
	while (s2[j + 1] != '\0')
		str[i++] = s2[j++ + 1];
	str[i] = C_TWO_QUOTE;
	str[i + 1] = '\0';
	return (str);
}

char	*ft_strjoin_env(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '=')
		j++;
	j++;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_join_env(char *str, char **env)
{
	char	**tmp;
	int		i;
	int		sust_flag;

	sust_flag = 0;
	i = 0;
	tmp = malloc(sizeof(char *) * (ft_array_len(env) + 2));
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (ft_strcmp_env(env[i], str) == 0)
		{
			tmp[i] = ft_strjoin_env(env[i], str);
			sust_flag = 1;
		}
		else
			tmp[i] = ft_strdup(env[i]);
		i++;
	}
	if (sust_flag == 0)
		tmp[i++] = ft_strdup_join(str);
	tmp[i] = NULL;
	ft_matrix_free(env);
	return (tmp);
}

char	**ft_join_export(char *str, char **export)
{
	char	**tmp;
	int		i;
	int		sust_flag;

	sust_flag = 0;
	i = 0;
	tmp = malloc(sizeof(char *) * (ft_array_len(export) + 2));
	if (!tmp)
		return (NULL);
	while (export[i])
	{
		if (ft_strcmp_export(export[i], str) == 0)
		{
			tmp[i] = ft_strjoin_export(export[i], str);
			sust_flag = 1;
		}
		else
			tmp[i] = ft_strdup(export[i]);
		i++;
	}
	if (sust_flag == 0)
		tmp[i++] = ft_strdup_export(str);
	tmp[i] = NULL;
	ft_matrix_free(export);
	return (tmp);
}
