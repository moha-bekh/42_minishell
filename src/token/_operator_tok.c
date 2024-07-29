/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _operator_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:23:00 by moha              #+#    #+#             */
/*   Updated: 2024/07/29 11:31:26 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_or(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, _OR, ft_substr(input, *i, 3));
	if (_tok_is(_STX_ERR_OR, token->t_bot->value[2]))
		return (_tok_syntax_err(token->t_bot->value[2], 1));
	token->t_bot->value[2] = '\0';
	*i += 2;
	return (IT_IS);
}

int	_tok_and(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, _AND, ft_substr(input, *i, 3));
	if (_tok_is(_STX_ERR_AND, token->t_bot->value[2]))
		return (_tok_syntax_err(token->t_bot->value[2], 1));
	token->t_bot->value[2] = '\0';
	*i += 2;
	return (IT_IS);
}

int	_tok_pipe(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, _PIPE, ft_substr(input, *i, 3));
	if (_tok_is(_STX_ERR_PIPE, token->t_bot->value[1]))
		return (_tok_syntax_err(token->t_bot->value[1], 1));
	token->t_bot->value[1] = '\0';
	token->t_bot->value[2] = '\0';
	*i += 1;
	return (IT_IS);
}

int	_tok_operator_process(char *input, u_padll token, int *i)
{
	if (token->t_top->value[*i] == '&' && token->t_top->value[*i + 1] == '&')
		return (_tok_and(input, token, i));
	else if (token->t_top->value[*i] == '|' && token->t_top->value[*i
		+ 1] == '|')
		return (_tok_or(input, token, i));
	else if (token->t_top->value[*i] == '|' && token->t_top->value[*i
		+ 1] != '|')
		return (_tok_pipe(input, token, i));
	else
		*i += 1;
	return (IS_NT);
}
