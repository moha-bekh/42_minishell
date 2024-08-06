/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redir_tok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:21:44 by moha              #+#    #+#             */
/*   Updated: 2024/07/30 16:22:59 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_set_redir_in(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, _REDIR_IN, ft_substr(input, *i, 3));
	if (_tok_is(_STX_ERR_REDIR_IN, token->t_bot->value[*i + 1]))
		return (_tok_syntax_err(token->t_bot->value[*i + 1], 1));
	token->t_bot->value[1] = '\0';
	// token->t_bot->value[2] = '\0';
	*i += 1;
	return (_IS);
}

int	_tok_set_redir_outt(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, _REDIR_OUTT, ft_substr(input, *i, 3));
	if (_tok_is(_STX_ERR_REDIR_OUTT, token->t_bot->value[*i + 1]))
		return (_tok_syntax_err(token->t_bot->value[*i + 1], 1));
	token->t_bot->value[1] = '\0';
	// token->t_bot->value[2] = '\0';
	*i += 1;
	return (_IS);
}

int	_tok_set_redir_outa(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, _REDIR_OUTA, ft_substr(input, *i, 3));
	if (_tok_is(_STX_ERR_REDIR_OUTA, token->t_bot->value[*i + 2]))
		return (_tok_syntax_err(token->t_bot->value[*i + 2], 1));
	token->t_bot->value[2] = '\0';
	*i += 2;
	return (_IS);
}

int	_tok_set_here_doc(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, _HERE_DOC, ft_substr(input, *i, 3));
	if (_tok_is(_STX_ERR_HERE_DOC, token->t_bot->value[*i + 2]))
		return (_tok_syntax_err(token->t_bot->value[*i + 2], 1));
	token->t_bot->value[2] = '\0';
	*i += 2;
	return (_IS);
}

int	_tok_redir_process(char *input, u_padll token, int *i)
{
	if (input[*i] == '<' && input[*i + 1] != '<')
		return (_tok_set_redir_in(input, token, i));
	else if (input[*i] == '<' && input[*i + 1] == '<')
		return (_tok_set_here_doc(input, token, i));
	else if (input[*i] == '>' && input[*i + 1] != '>')
		return (_tok_set_redir_outt(input, token, i));
	else if (input[*i] == '>' && input[*i + 1] == '>')
		return (_tok_set_redir_outa(input, token, i));
	return (_SUCCESS);
}
