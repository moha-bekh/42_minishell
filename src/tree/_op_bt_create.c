/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:22:59 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/26 19:03:10 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_create(char type, t_ptok token)
{
	t_pbt_op	tree;

	tree = NULL;
	if (_alloc((void **)&tree, sizeof(t_bt_op)))
		return (NULL);
	tree->type= type;
	tree->token = token;
	tree->cmd_a = NULL;
	tree->redir.here_name = NULL;
	tree->left = NULL;
	tree->root = NULL;
	tree->right = NULL;
	return (tree);
}
