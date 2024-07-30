/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check_tok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:20:49 by moha              #+#    #+#             */
/*   Updated: 2024/07/30 22:09:08 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_check_operator(u_padll tokens)
{
	t_ptok	tmp;

	if (!tokens->t_top->next)
		return (_EMPTY);
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

	if (!tokens->t_top->next)
		return (_EMPTY);
	tmp = tokens->t_top->next;
	if (tmp->type == '|')
		return (_tok_syntax_err('|', 1));
	if (tokens->t_bot->type == '|')
		return (_tok_syntax_err('|', 1));
	return (RET_OK);
}
int	_tok_check_redir(u_padll tokens)
{
	t_ptok	tmp;

	if (!tokens)
		return (_EMPTY);
	tmp = tokens->t_top->next;
	while (tmp)
	{
		if (_tok_is(_TYPE_REDIRS, tmp->type) && !tmp->next)
			ft_putstr_fd(_STX_ERR_REDIR, STDERR_FILENO);
		tmp = tmp->next;
	}
	return (RET_OK);
}

int	_tok_check(u_padll tokens)
{
	// t_ptok	tmp;

	if (!tokens || !tokens->t_top->next)
		return (_EMPTY);
	// tmp = tokens->t_top;
	if (_tok_check_operator(tokens) == -1 || _tok_check_pipe(tokens) == -1)
		return (_ERROR);
	if (_tok_check_redir(tokens) == -1)
		return (_ERROR);
	return (RET_OK);
}
