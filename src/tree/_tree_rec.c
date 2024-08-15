/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tree_rec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 12:07:54 by moha              #+#    #+#             */
/*   Updated: 2024/08/15 13:21:31 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_pbt_op	_tree(t_pdata data, t_ptok token)
// {
// 	if (!data || !token)
// 		return (NULL);
// 	if (token->type == _AND || token->type == _OR)
// 	{
// 		data->tree = _op_bt_push_root(data->tree, _op_bt_create(token->type, token));
// 		_tree(data, token->next);
// 	}
// 	else if (token->type == '(')
// 	{
// 		while (token->type != ')')
// 			_tree(data, token->next);
// 	}
// 	else if (token->type == _WORD)
// 	{
// 		data->tree = _op_bt_push_right(data->tree, _op_bt_create(token->type, token));
// 		while (token->next && !_tok_is(_TYP_SEP, token->next->type))
// 			token = token->next;
// 		_tree(data, token->next);
// 	}
// 	return (data->tree);
// }
