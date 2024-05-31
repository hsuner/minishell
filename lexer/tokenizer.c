/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:22:11 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 02:22:12 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_token(char *str, int i, t_lex *new)
{
	int	count;

	if (str[i] == C_VERTICAL_BAR)
		new->token = PIPE;
	else if (str[i] == C_LESS && str[i + 1] != C_LESS)
		new->token = LESS;
	else if (str[i] == C_LESS && str[i + 1] == C_LESS)
		new->token = LESS_LESS;
	else if (str[i] == C_GREAT && str[i + 1] != C_GREAT)
		new->token = GREAT;
	else if (str[i] == C_GREAT && str[i + 1] == C_GREAT)
		new->token = GREAT_GREAT;
	if (new->token == LESS_LESS || new->token == GREAT_GREAT)
		count = 2;
	else
		count = 1;
	return (count);
}

int	create_word(char *str, int i, t_lex *new)
{
	char	*word;
	int		j;

	j = 0;
	while (str[i + j])
	{
		if (str[i + j] == '\"' || str[i + j] == '\'')
		{
			j = ignore_quote(str, (i + j));
			j -= i;
		}
		if ((ft_isspace(str[i + j]) || ft_isreserved(str[i + j])))
			break ;
		j++;
	}
	word = ft_substr(str, i, j);
	if (!word)
		return (-1);
	new->word = word;
	return (j);
}

int	initialize_lexer_node(t_lex *new, char *str, int i)
{
	int		temp;

	if (ft_isreserved(str[i]))
		i += create_token(str, i, new);
	else
	{
		temp = create_word(str, i, new);
		if (temp == -1)
			return (-1);
		i += temp;
	}
	return (i);
}

int	tokenizer(char *str, t_lex **lexer)
{
	t_lex	*new;
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
		{
			new = lexer_lstnew();
			if (!new)
				return (1);
			lexer_lstadd_back(lexer, new);
			i = initialize_lexer_node(new, str, i);
			if (i == -1)
				return (1);
		}
		else
			i++;
	}
	return (0);
}
