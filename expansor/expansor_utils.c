/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:23:51 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 02:23:53 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

void	init_quote(t_quote	*quote)
{
	quote->one = 0;
	quote->two = 0;
}

void	find_quote(t_quote *quote, int i, char *str)
{
	if (str[i] == C_TWO_QUOTE && quote->one == 0 && quote->two == 0)
		quote->two = 1;
	else if (str[i] == C_TWO_QUOTE && quote->one == 0 && quote->two == 1)
		quote->two = 0;
	if (str[i] == C_ONE_QUOTE && quote->one == 0 && quote->two == 0)
		quote->one = 1;
	else if (str[i] == C_ONE_QUOTE && quote->one == 1 && quote->two == 0)
		quote->one = 0;
}

int	calc_len_expan(char *str, char **env, int status)
{
	int		i;
	int		len;
	t_quote	quote;

	i = 0;
	len = 0;
	init_quote(&quote);
	while (str[i] != '\0')
	{
		find_quote(&quote, i, str);
		if ((str[i] == '$' || str[i] == '~') && quote.one == 0)
			i += calc_len_value_expan(&str[i], env, status, &len);
		else
			len++;
		i++;
	}
	return (len);
}

int	ft_omit_var(char *var)
{
	int	i;

	i = 1;
	if (var[i] == '?')
		return (2);
	while (ft_isalnum(var[i]) || var[i] == '_')
		i++;
	return (i);
}

char	*obtain_var(char *str)
{
	char	*var;
	int		i;

	i = 0;
	str++;
	var = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!var)
		return (NULL);
	while (ft_isalnum(str[i]) == 1 || str[i] == '_')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}
