/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:20:07 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/24 14:19:18 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <signal.h>

static void	sig_handler_def(int signum)
{
	if (g_signal == 10)
	{
		if (signum == CTRL_C)
		{
			ft_printf("\n");
			exit(1);
		}
	}
	else if (!g_signal && signum == CTRL_C)
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == CTRL_SLASH)
		;
}

int	init_signals(void)
{
	signal(CTRL_C, sig_handler_def);
	signal(CTRL_SLASH, sig_handler_def);
	return (1);
}
