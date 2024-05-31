/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:21:02 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 16:04:33 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*enve;

	(void)av;
	if (ac != 1)
	{
		ft_printf_fd(STDERR_FILENO, MSSG_INVALID_ARGS);
		return (1);
	}
	enve = ft_dup_matrix_env(envp);
	if (!enve)
	{
		ft_printf_fd(STDERR_FILENO, MSSG_MEMORY_ERROR);
		return (0);
	}
	init_signals();
	generate_terminal(enve);
	return (0);
}
