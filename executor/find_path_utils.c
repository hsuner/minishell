/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:24:57 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 02:24:58 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	search_extra_path(char *cmd, char *envp, char **path, int exit_status)
{
	if (exit_status == CMD_NOT_FOUND)
		exit_status = try_local_path(cmd, path);
	if (exit_status == CMD_NOT_FOUND)
		exit_status = try_absolute_path(cmd, path);
	if (exit_status == CMD_NOT_FOUND && !envp)
		return (NO_SUCH_FILE);
	return (exit_status);
}
