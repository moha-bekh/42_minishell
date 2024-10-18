/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bt_push_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:33:18 by moha              #+#    #+#             */
/*   Updated: 2024/10/18 13:36:24 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_bt_push_left(t_ppbtree node, t_pbtree new)
{
	if (!(*node))
		(*node) = new;
	else
	{
		(*node)->left = new;
		new->root = (*node);
	}
}
