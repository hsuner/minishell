/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:25:03 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/24 14:24:16 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <fcntl.h>
#include <stdlib.h>

void	unlink_heredocs(t_io *redirection)
{
	while (redirection)
	{
		if (redirection->type == HERE_DOC)
			unlink(redirection->file);
		redirection = redirection->next;
	}
}

void	close_pipe(int in, int out)
{
	if (in != -1)
		close(in);
	if (out != -1)
		close(out);
}

int	dup_custom_redirections(t_pipe *data, t_io *temp)
{
	if (temp->type == IN || temp->type == HERE_DOC)
	{
		data->fd_in = open(temp->file, O_RDONLY);
		if (data->fd_in < 0)
			return (1);
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	else if (temp->type == OUT_TRUNC || temp->type == OUT_APPEND)
	{
		if (temp->type == OUT_TRUNC)
			data->fd_out = open(temp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			data->fd_out = open(temp->file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		if (data->fd_out < 0)
			return (1);
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	return (0);
}

int	manage_redirections(t_cmd *commands, t_pipe *data, int out)
{
	t_io	*temp;

	if (commands->next != NULL)
		dup2(data->fd[1], STDOUT_FILENO);
	close_pipe(data->fd[0], data->fd[1]);
	temp = commands->redirect;
	while (temp)
	{
		if (dup_custom_redirections(data, temp) == 1)
		{
			unlink_heredocs(commands->redirect);
			if (out == FT_RETURN)
				return (perror_return(data, 1, temp->file));
			else
				perror_exit(data, EXIT_FAILURE, temp->file);
		}
		temp = temp->next;
	}
	unlink_heredocs(commands->redirect);
	return (0);
}
