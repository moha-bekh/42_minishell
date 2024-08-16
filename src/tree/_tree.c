/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:26:15 by moha              #+#    #+#             */
/*   Updated: 2024/08/09 12:29:33 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_ptr_recovery(t_pbt_op tree, u_padll *scop)
{
	(*scop)->s_bot->ptr_op->right = tree;
	tree->root = (*scop)->s_bot->ptr_op;
	tree = (*scop)->s_bot->ptr_op;
	(*scop) = _scp_pop_back((*scop));
	return (tree);
}

t_pbt_op	_tree(t_pdata data)
{
	t_ptok	tok;

	if (!data || !data->tok)
		return (NULL);
	tok = data->tok->t_top;
	while (tok)
	{
		if (tok->type == _AND)
			data->tree = _op_bt_push_root(data->tree, _op_bt_create(tok->type,
						tok));
		else if (tok->type == _OR)
			data->tree = _op_bt_push_root(data->tree, _op_bt_create(tok->type,
						tok));
		else if (tok->type == '(')
		{
			data->scp = _scp_push_back(data->scp, data->tree);
			data->tree = NULL;
		}
		else if (tok->type == ')')
			data->tree = _ptr_recovery(data->tree, &data->scp);
		else
		{
			data->tree = _op_bt_push_right(data->tree, _op_bt_create(tok->type,
						tok));
			while (tok->next && !_tok_is(_TYP_SEP, tok->next->type))
				tok = tok->next;
		}
		tok = tok->next;
	}
	return (data->tree);
}

// t_pbt_op	_tree(t_pdata data, t_ptok token)
// {
// 	if (!data || !token)
// 		return (NULL);
// 	if (token->type == _AND || token->type == _OR)
// 	{
// 		data->tree = _op_bt_push_root(data->tree, _op_bt_create(token->type,
// 					token));
// 		_tree(data, token->next);
// 	}
// 	else if (token->type == _WORD)
// 	{
// 		data->tree = _op_bt_push_right(data->tree, _op_bt_create(token->type,
// 					token));
// 		while (token->next && !_tok_is(_TYP_SEP, token->next->type))
// 			token = token->next;
// 		_tree(data, token->next);
// 	}
// 	else if (token->type == '(')
// 		_tree(data, token->next);
// 	else if (token->type == ')')
// 		return (data->tree);
// 	return (data->tree);
// }
