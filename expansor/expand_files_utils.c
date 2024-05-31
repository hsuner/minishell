/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_files_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:23:34 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 02:23:35 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>
#include <fcntl.h>

int	rewrite_file(char *path, char **aux)
{
	int	fd;
	int	i;

	fd = open(path, O_TRUNC | O_WRONLY);
	if (fd == -1)
		return (1);
	i = 0;
	while (aux[i])
	{
		ft_printf_fd(fd, "%s", aux[i]);
		i++;
	}
	close(fd);
	return (0);
}

int	calc_len_file(char *path)
{
	int		fd;
	char	*str;
	int		len;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	str = get_next_line(fd);
	if (!str)
		return (0);
	len = 1;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		len++;
	}
	close(fd);
	return (len);
}

int	fill_aux(char *path, char **file)
{
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	i = 0;
	file[i] = get_next_line(fd);
	while (file[i])
	{
		i++;
		file[i] = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	expand_vars_file(char **file, char **aux, char **env, int status)
{
	int		i;

	i = 0;
	while (file[i])
	{
		aux[i] = malloc(sizeof(char *) * (calc_len_expan_file \
		(file[i], env, status) + 1));
		if (!aux[i])
		{
			ft_free_matrix(aux, i);
			return (1);
		}
		ft_bzero(aux[i], calc_len_expan_file(file[i], env, status) + 1);
		check_expand_file(file[i], status, aux[i], env);
		i++;
	}
	aux[i] = NULL;
	return (0);
}
