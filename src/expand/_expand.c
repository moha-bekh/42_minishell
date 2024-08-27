/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:22:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/27 17:38:49 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_expand_line(t_ppnlst token)
{
	t_pnlst	tmp;

	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_token_id(tmp->x, _TYP_SEP))
	{
		if (tmp->x == '*' && _expand_wildcards(&tmp))
			return (_FAILURE);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}

// int	_varchr_conv(char c)
// {
// 	if (ft_isalnum(c) || c == '_' || c == '?')
// 		return (1);
// 	return (0);
// }

// int	_expand_env_var(t_pdata data, t_ptok token)
// {
// 	char	*value;

// 	value = _get_env_value(data->env.dll_env, token->value);
// 	free(token->value);
// 	token->value = value;
// 	return (_SUCCESS);
// }

// int	_expand_errno(t_pdata data, t_ptok token)
// {
// 	char	*value;
// 	char	*tmp;

// 	tmp = ft_itoa(data->_errno);
// 	value = ft_strjoin(tmp, token->value + 1);
// 	free(token->value);
// 	free(tmp);
// 	token->value = value;
// 	return (_SUCCESS);
// }

// int	_expand(t_pdata data)
// {
// 	t_ptok	tmp;

// 	if (!data || !data->tok)
// 		return (_FAILURE);
// 	tmp = data->tok->t_top;
// 	while (tmp)
// 	{
// 		if (tmp->type == '$' && tmp->next)
// 		{
// 			tmp = tmp->next;
// 			data->tok = _tok_pop_in(data->tok, tmp->prev);
// 			if (tmp->value[0] == '?')
// 				_expand_errno(data, tmp);
// 			else
// 				_expand_env_var(data, tmp);
// 		}
// 		if (tmp->type == '"' && tmp->value[0])
// 			_expand_string(data, tmp);
// 		tmp = tmp->next;
// 	}
// 	return (_SUCCESS);
// }
