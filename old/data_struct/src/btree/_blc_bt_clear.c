/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _blc_bt_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:26:42 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 22:42:31 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_blc_bt_clear(t_pbt_blc tree)
{
	if (!tree)
		return ;
	_blc_bt_clear(tree->left);
	_blc_bt_clear(tree->right);
	ft_free_arr(tree->cmds);
	free(tree);
	return ;
}
