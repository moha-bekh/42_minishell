/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_bt_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:25:10 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 22:41:48 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

int	_tok_bt_size(t_pbt_tok tree)
{
	if (!tree)
		return (0);
	return (1 + _tok_bt_size(tree->left) + _tok_bt_size(tree->right));
}
