/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:20:49 by moha              #+#    #+#             */
/*   Updated: 2024/07/23 22:20:53 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_check_operator(u_padll tokens)
{
	t_ptok	tmp;

	tmp = tokens->t_top->next;
	if (tmp->type == 'A' || tmp->type == 'O')
		return (_tok_syntax_err(tmp->value[0], 2));
	if (tokens->t_bot->type == 'A' || tokens->t_bot->type == 'O')
		return (_tok_syntax_err(tokens->t_bot->value[0], 2));
	return (RET_OK);
}

int	_tok_check_pipe(u_padll tokens)
{
	t_ptok	tmp;

	tmp = tokens->t_top->next;
	if (tmp->type == '|')
		return (_tok_syntax_err('|', 1));
	if (tokens->t_bot->type == '|')
		return (_tok_syntax_err('|', 1));
	return (RET_OK);
}
int	_tok_check_redir(t_ptok tok)
{
	if (_tok_is(_REDIRS, tok->value[0]) && tok->next->type != _LITERAL)
		return (_tok_syntax_err(tok->next->value[0], 2));
	return (RET_OK);
}

int	_tok_check(u_padll tokens)
{
	t_ptok	tmp;

	tmp = tokens->t_top;
	if (_tok_check_operator(tokens) == -1 || _tok_check_pipe(tokens) == -1)
		return (RET_ERR);
	while (tmp)
	{
		if (_tok_check_redir(tmp) == -1)
			return (RET_ERR);
		tmp = tmp->next;
	}
	return (RET_OK);
}
