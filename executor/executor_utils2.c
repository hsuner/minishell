/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:24:44 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 02:24:45 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

int	is_builtin(t_cmd *commands)
{
	if (commands && commands->args && commands->args[0])
	{
		if (ft_strcmp_nocase(commands->args[0], "echo") == 0)
			return (1);
		else if (ft_strcmp_nocase(commands->args[0], "cd") == 0)
			return (1);
		else if (ft_strcmp_nocase(commands->args[0], "pwd") == 0)
			return (1);
		else if (ft_strcmp(commands->args[0], "export") == 0)
			return (1);
		else if (ft_strcmp(commands->args[0], "unset") == 0)
			return (1);
		else if (ft_strcmp_nocase(commands->args[0], "env") == 0)
			return (1);
		else if (ft_strcmp(commands->args[0], "exit") == 0)
			return (1);
	}
	return (0);
}

void	execute_builtins(char **args, t_env *envp, int *exit_s, int exit_flag)
{
	if (ft_strcmp_nocase(args[0], "echo") == 0)
		*exit_s = ft_echo(args);
	else if (ft_strcmp_nocase(args[0], "cd") == 0)
		*exit_s = ft_cd(args, &envp->env);
	else if (ft_strcmp_nocase(args[0], "pwd") == 0)
		*exit_s = ft_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		*exit_s = ft_export(args, envp);
	else if (ft_strcmp(args[0], "unset") == 0)
		*exit_s = ft_unset(args, envp);
	else if (ft_strcmp_nocase(args[0], "env") == 0)
		*exit_s = ft_env(envp->env);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args, exit_s);
	if (exit_flag == FT_EXIT)
		exit(*exit_s);
}
