/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tree_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:26:15 by moha              #+#    #+#             */
/*   Updated: 2024/07/26 18:44:03 by mbekheir         ###   ########.fr       */
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

t_pbt_op	_tree_process(t_pdata data)
{
	t_ptok	tok;

	tok = data->tok->t_top->next;
	while (tok)
	{
		if (tok->type == _AND || tok->type == _OR)
			data->tree = _op_bt_push_root(data->tree, _op_bt_create(tok->type, tok));
		if (tok->type == _OPEN_PAR)
		{
			data->scop = _scp_push_back(data->scop, data->tree);
			data->tree = NULL;
		}
		else if (tok->type == _CLOSE_PAR)
			data->tree = _ptr_recovery(data->tree, &data->scop);
		else if (_tok_is(_TREE_SEP, tok->prev->type))
			data->tree = _op_bt_push_right(data->tree, _op_bt_create(tok->type, tok));
		tok = tok->next;
	}
	return (data->tree);
}
