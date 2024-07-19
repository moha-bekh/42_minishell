/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_bt_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:16:18 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 22:42:07 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_tok_bt_clear(t_pbt_tok tree)
{
	if (!tree)
		return ;
	_tok_bt_clear(tree->left);
	_tok_bt_clear(tree->right);
	free(tree->value);
	tree->value = NULL;
	free(tree);
	tree = NULL;
	return ;
}
