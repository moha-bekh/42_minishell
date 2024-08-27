/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bt_push_root.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:51:02 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 15:55:13 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_bt_push_root(t_ppbtree node, t_pbtree new)
{
	if (!(*node))
		(*node) = new;
	else
	{
		new->left = (*node);
		(*node)->root = new;
		(*node) = new;
	}
}
