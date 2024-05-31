/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbosnak <bbosnak@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:22:24 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/22 02:22:26 by bbosnak          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_isquote(int c)
{
	if (c == C_ONE_QUOTE || c == C_TWO_QUOTE)
		return (1);
	return (0);
}

int	ft_isreserved(int c)
{
	if (c == C_VERTICAL_BAR || c == C_LESS || c == C_GREAT)
		return (1);
	return (0);
}

void	print_tokens(t_lex *lexer, char *str)
{
	printf("entry: %s\n", str);
	printf("token: ");
	while (lexer)
	{
		if (lexer->token != NONE)
		{
			if (lexer->token == PIPE)
				printf("PIPE===");
			else if (lexer->token == LESS)
				printf("LESS===");
			else if (lexer->token == LESS_LESS)
				printf("LESS_LESS===");
			else if (lexer->token == GREAT)
				printf("GREAT===");
			else if (lexer->token == GREAT_GREAT)
				printf("GREAT_GREAT===");
		}
		else
			printf("%s===", lexer->word);
		lexer = lexer->next;
	}
	printf("\n");
}
