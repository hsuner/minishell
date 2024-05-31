/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:25:18 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/23 20:20:27 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	string_to_command(char *str, t_cmd **commands, t_env *env, int *exit_s)
{
	int		status;
	t_lex	*lexer;

	lexer = NULL;
	*commands = NULL;
	status = tokenizer(str, &lexer);
	if (status == 0)
		status = parser(commands, &lexer, exit_s);
	if (status == 0)
	{
		status = heredoc(*commands);
		if (status == 1)
		{
			lexer_lstclear(&lexer);
			return (*exit_s = 1, 1);
		}
	}
	if (status == 0)
		status = expansor(*commands, env->env, *exit_s);
	if (status == 0)
		status = expansor_files(*commands, env->env, *exit_s);
	if (status == 1)
		ft_printf_fd(STDERR_FILENO, MSSG_MEMORY_ERROR);
	lexer_lstclear(&lexer);
	return (status);
}

void	generate_terminal2(char *str, t_env *env, int exit_s, t_cmd *cmd)
{
	while (str)
	{
		add_history(str);
		if (quote_check(str, 1) && string_to_command(str, &cmd, env, &exit_s) \
		== 0 && cmd != NULL)
		{
			if (execute_commands(cmd, env, &exit_s) == 1)
				ft_printf_fd(STDERR_FILENO, MSSG_EXECUTOR_ERROR);
			parser_lstclear(&cmd);
		}
		else if (quote_check(str, 0) && cmd != NULL)
			parser_lstclear(&cmd);
		free(str);
		g_signal = 0;
		str = readline("\x1b[32;01mminishell$ \x1b[0m");
		g_signal = 1;
	}
	ft_matrix_free(env->env);
	ft_matrix_free(env->export);
	exit(exit_s);
}

void	generate_terminal(t_env *env)
{
	int		exit_s;
	t_cmd	*cmd;
	char	*str;

	cmd = NULL;
	str = readline("\x1b[32;01mminishell$ \x1b[0m");
	((1) && (exit_s = 0) && (g_signal = 1));
	generate_terminal2(str, env, exit_s, cmd);
}
