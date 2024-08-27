/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bt_push_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:33:18 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 15:55:03 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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