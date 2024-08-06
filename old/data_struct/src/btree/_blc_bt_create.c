/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _blc_bt_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:26:27 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 22:43:19 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pbt_blc	_blc_bt_create(void)
{
	t_pbt_blc	tree;

	if (_alloc((void *)&tree, sizeof(t_bt_blc)))
		return (NULL);
	ft_memset(tree, 0, sizeof(t_bt_blc));
	tree->cmds = NULL;
	tree->left = NULL;
	tree->root = NULL;
	tree->right = NULL;
	return (tree);
}
