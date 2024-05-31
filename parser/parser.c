/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsuner <hsuner@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 02:21:35 by bbosnak           #+#    #+#             */
/*   Updated: 2024/01/23 16:56:51 by hsuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

int	count_arguments(t_lex *lexer)
{
	int	i;

	i = 0;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->token == NONE)
		{
			if (!lexer->prev)
				i++;
			else if (lexer->prev->token == NONE || lexer->prev->token == PIPE)
				i++;
		}
		lexer = lexer->next;
	}
	return (i);
}

int	add_redirection(t_io **redirect, t_lex **head)
{
	t_lex	*temp;
	t_io	*new;

	temp = *head;
	new = redirect_lstnew();
	if (!new)
		return (1);
	redirect_lstadd_back(redirect, new);
	if (temp->token == LESS)
		new->type = IN;
	else if (temp->token == LESS_LESS)
		new->type = HERE_DOC;
	else if (temp->token == GREAT)
		new->type = OUT_TRUNC;
	else if (temp->token == GREAT_GREAT)
		new->type = OUT_APPEND;
	new->file = ft_strdup(temp->next->word);
	if (!new->file)
		return (1);
	*head = (*head)->next;
	return (0);
}

int	fill_command(t_lex **head, t_io **redirect, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (*head && (*head)->token != PIPE)
	{
		if ((*head)->token != NONE)
		{
			if (add_redirection(redirect, head) == 1)
				return (1);
		}
		else
		{
			cmd->args[i] = ft_strdup((*head)->word);
			if (!cmd->args[i])
			{
				cmd->args = ft_free_matrix(cmd->args, i);
				return (1);
			}
			i++;
		}
		*head = (*head)->next;
	}
	cmd->redirect = *redirect;
	return (0);
}

int	create_simple_command(t_lex **head, t_cmd *cmd)
{
	int		n_args;
	t_io	*redirect;

	redirect = NULL;
	n_args = count_arguments(*head);
	cmd->args = malloc(sizeof(char *) * (n_args + 1));
	if (!cmd->args)
		return (1);
	cmd->args[n_args] = NULL;
	if (fill_command(head, &redirect, cmd) == 1)
		return (1);
	if (*head && (*head)->token == PIPE)
		*head = (*head)->next;
	return (0);
}

int	parser(t_cmd **commands, t_lex **lexer, int *exit_s)
{
	t_cmd	*new;
	t_lex	*head;

	if (!lexer)
		return (0);
	if (check_syntax_error(*lexer, exit_s) == SYNTAX_ERR)
		return (lexer_lstclear(lexer), SYNTAX_ERR);
	head = *lexer;
	while (head)
	{
		new = parser_lstnew();
		if (!new)
			return (1);
		parser_lstadd_back(commands, new);
		if (create_simple_command(&head, new) == 1)
			return (1);
	}
	return (0);
}
