/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bt_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:26:47 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/31 16:02:54 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_bt_clear(t_ppbtree node)
{
	if (!*node)
		return ;
	if ((*node)->left)
		_bt_clear(&(*node)->left);
	if ((*node)->right)
		_bt_clear(&(*node)->right);
	_cmd_clear(&(*node)->cmd_line);
	free((*node));
	(*node) = NULL;
}
