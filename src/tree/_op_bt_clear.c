/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _op_bt_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:26:47 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/29 11:37:20 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pbt_op	_op_bt_clear(t_pbt_op tree)
{
	if (!tree)
		return (NULL);
	_op_bt_clear(tree->left);
	_op_bt_clear(tree->right);
	free(tree->cmd_a);
	// free(tree->redir.here_name);
	free(tree);
	tree = NULL;
	return (tree);
}
