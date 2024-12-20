/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bt_push_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:51:16 by moha              #+#    #+#             */
/*   Updated: 2024/08/31 16:03:11 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_bt_push_right(t_ppbtree node, t_pbtree new)
{
	if (!(*node))
		(*node) = new;
	else
	{
		(*node)->right = new;
		new->root = (*node);
	}
}
