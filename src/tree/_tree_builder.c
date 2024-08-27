/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tree_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:26:15 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 16:49:42 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pnlst	_cmd_node(t_ppbtree node, t_pnlst token)
{
	t_pbtree	tmp_node;
	t_pnlst		tmp_token;

	if (!token)
		return (NULL);
	*node = NULL;
	tmp_node = NULL;
	tmp_token = NULL;
	if (token->x == '(')
	{
		tmp_token = token;
		token = _tree_builder(&tmp_node, token->next);
		*node = _bt_join(*node, tmp_token, tmp_node);
		if (token && token->x == ')')
			token = token->next;
	}
	else
	{
		*node = _bt_create(token);
		while (token && token->x != _AND && token->x != _OR)
			token = token->next;
	}
	return (token);
}

t_pnlst	_tree_builder(t_ppbtree node, t_pnlst token)
{
	t_pbtree	tmp_node;
	t_pnlst		tmp_token;

	token = _cmd_node(node, token);
	while (token && (token->x == _AND || token->x == _OR))
	{
		tmp_token = token;
		token = _cmd_node(&tmp_node, token->next);
		*node = _bt_join(*node, tmp_token, tmp_node);
	}
	return (token);
}
