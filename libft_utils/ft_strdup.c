/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:29:11 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 02:29:12 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*var;

	i = ft_strlen(s1) + 1;
	var = malloc(i * sizeof(char));
	if (!var)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		var[i] = s1[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}
