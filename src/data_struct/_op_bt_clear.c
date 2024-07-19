/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:26:47 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 22:24:49 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_clear(t_pbt_op tree)
{
	if (!tree)
		return (NULL);
	_op_bt_clear(tree->left);
	_op_bt_clear(tree->right);
	free(tree);
	tree = NULL;
	return (tree);
}
