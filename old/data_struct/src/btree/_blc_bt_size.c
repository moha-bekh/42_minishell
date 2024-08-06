/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _blc_bt_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:27:05 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 22:42:10 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

int	_blc_bt_size(t_pbt_blc tree)
{
	if (!tree)
		return (0);
	return (1 + _blc_bt_size(tree->left) + _blc_bt_size(tree->right));
}
