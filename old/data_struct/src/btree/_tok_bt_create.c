/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_bt_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:16:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 20:23:38 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pbt_tok	_tok_bt_create(char *value, char type)
{
	t_pbt_tok	tree;

	tree = NULL;
	if (_alloc((void **)&tree, sizeof(t_bt_tok)))
		return (NULL);
	tree->value = value;
	tree->type = type;
	tree->join = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}
