/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:21:44 by moha              #+#    #+#             */
/*   Updated: 2024/07/23 22:22:36 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_tok_set_redir_in(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, '<', ft_substr(input, *i, 3));
	// if (_tok_is(_SYNTAX_REDIR_IN_ERR, value[*i + 1]))
	// 	return (_tok_syntax_err(value[*i + 1], 1));
	token->t_bot->value[1] = '\0';
	token->t_bot->value[2] = '\0';
	*i += 1;
	return (IT_IS);
}

int	_tok_set_redir_outt(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, '>', ft_substr(input, *i, 3));
	// if (_tok_is(_SYNTAX_REDIR_OUTT_ERR, value[*i + 1]))
	// 	return (_tok_syntax_err(value[*i + 1], 1));
	token->t_bot->value[1] = '\0';
	token->t_bot->value[2] = '\0';
	*i += 1;
	return (IT_IS);
}

int	_tok_set_redir_outa(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, 'N', ft_substr(input, *i, 3));
	// if (_tok_is(_SYNTAX_REDIR_OUTA_ERR, value[*i + 2]))
	// 	return (_tok_syntax_err(value[*i + 2], 1));
	token->t_bot->value[2] = '\0';
	*i += 2;
	return (IT_IS);
}

int	_tok_set_here_doc(char *input, u_padll token, int *i)
{
	token = _tok_push_back(token, 'H', ft_substr(input, *i, 3));
	// if (_tok_is(_SYNTAX_HERE_DOC_ERR, value[*i + 2]))
	// 	return (_tok_syntax_err(value[*i + 2], 1));
	token->t_bot->value[2] = '\0';
	*i += 2;
	return (IT_IS);
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
	return (EXIT_SUCCESS);
}
