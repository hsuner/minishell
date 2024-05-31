/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:20:42 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 11:01:08 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

t_env	*generate_env(char **envp)
{
	t_env	*dup;

	dup = malloc(sizeof(t_env));
	if (!dup)
		return (NULL);
	dup->env = malloc((ft_array_len(envp) + 1) * sizeof(char *));
	if (!dup->env)
		return (free(dup), NULL);
	dup->export = malloc((ft_array_len(envp) + 1) * sizeof(char *));
	if (!dup->export)
		return (free(dup->env), free(dup), NULL);
	return (dup);
}

char	*find_shlvl(char **envp)
{
	int		i;
	int		flag;
	char	*aux;

	i = 0;
	flag = 0;
	while (envp[i] && flag == 0)
	{
		if (ft_strcmp_env(envp[i], "SHLVL") == 0)
			flag = 1;
		i++;
	}
	if (flag == 0)
	{
		aux = ft_strdup("SHLVL=1");
		if (!aux)
			return (ft_free_matrix(envp, i), NULL);
		return (aux);
	}
	return (NULL);
}

t_env	*ft_check_new_shlvl(t_env *dup, int i)
{
	if (dup->env[i] != NULL)
	{
		dup->export[i] = ft_strdup_export(dup->env[i]);
		if (!dup->export[i])
			return (ft_free_matrix(dup->env, i), ft_free_matrix(dup->export, i),
				free(dup), NULL);
		i++;
	}
	dup->env[i] = NULL;
	dup->export[i] = NULL;
	return (dup);
}

t_env	*ft_dup_matrix_env(char **envp)
{
	t_env	*dup;
	int		i;

	i = 0;
	dup = generate_env(envp);
	while (envp[i])
	{
		if (ft_strcmp_env(envp[i], "SHLVL") == 0)
			dup->env[i] = ft_correct_shlvl(envp[i]);
		else
			dup->env[i] = ft_strdup(envp[i]);
		if (!dup->env[i])
			return (ft_free_matrix(dup->env, i), free(dup), NULL);
		dup->export[i] = ft_strdup_export(dup->env[i]);
		if (!dup->export[i])
			return (ft_free_matrix(dup->env, i), ft_free_matrix(dup->export, i),
				free(dup), NULL);
		i++;
	}
	dup->env[i] = find_shlvl(envp);
	dup = ft_check_new_shlvl(dup, i);
	return (dup);
}
