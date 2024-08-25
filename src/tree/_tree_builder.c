/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tree_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:26:15 by moha              #+#    #+#             */
/*   Updated: 2024/08/25 01:45:53 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbtree	_op_node(t_pnlst *token);

t_pbtree	_cmd_node(t_pnlst *token)
{
	t_pbtree	node;

	if (!*token)
		return (NULL);
	node = NULL;
	if ((*token)->x == '(')
	{
		node = _bt_join(node, *token, _op_node(&(*token)->next));
		*token = (*token)->next;
		if (*token && (*token)->x == ')')
			*token = (*token)->next;
	}
	else
	{
		node = _bt_create(*token);
		while (*token && (*token)->x != _AND && (*token)->x != _OR)
			*token = (*token)->next;
	}
	return (node);
}

t_pbtree	_op_node(t_pnlst *token)
{
	t_pbtree	node;

	node = _cmd_node(token);
	while (*token && ((*token)->x == _AND || (*token)->x == _OR))
	{
		node = _bt_join(node, *token, _cmd_node(&(*token)->next));
		*token = (*token)->next;
	}
	return (node);
}

t_pbtree	_tree_builder(t_pdata data)
{
	t_pnlst	tmp;

	tmp = data->tokens->d_top;
	return (_op_node(&tmp));
}
