/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:29:01 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 03:13:03 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;
	size_t	i;

	if (!dest)
	{
		dest = malloc(1);
		if (!dest)
			return (NULL);
		dest[0] = '\0';
	}
	if (!src)
		return (dest);
	dest_len = ft_strlen(dest);
	i = -1;
	while (src[++i] != '\0')
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}
