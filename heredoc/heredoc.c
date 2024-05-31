/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:23:01 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 05:14:36 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>

void	create_heredoc(char *delimiter, char *path)
{
	char	*str;
	int		fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	g_signal = 10;
	str = readline("> ");
	while (str && ft_strcmp(delimiter, str) != 0)
	{
		str = ft_strjoin_line(str, "\n");
		ft_putstr_fd(str, fd);
		free(str);
		str = readline("> ");
	}
	close(fd);
	free(str);
}

int	do_heredoc(int i, t_io *aux)
{
	char	*num;
	char	*path;
	int		status;
	pid_t	pid;

	num = ft_itoa(i);
	path = ft_strjoin("/tmp/minishell", num);
	free(num);
	pid = fork();
	if (pid < 0)
		ft_printf_fd(STDERR_FILENO, MSSG_FORK_ERROR);
	if (pid == 0)
	{
		create_heredoc(aux->file, path);
		exit(0);
	}
	waitpid(pid, &status, 0);
	free(aux->file);
	aux->file = ft_strdup(path);
	free(path);
	return (status);
}

int	heredoc(t_cmd *commands)
{
	t_io	*aux;
	int		i;

	i = 0;
	while (commands)
	{
		aux = commands->redirect;
		while (aux)
		{
			if (aux->type == HERE_DOC)
			{
				if (do_heredoc(i, aux))
					return (1);
				i++;
			}
			aux = aux->next;
		}
		commands = commands->next;
	}
	return (0);
}
