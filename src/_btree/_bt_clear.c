/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bt_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:26:47 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/24 02:34:12 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_bt_clear(t_pbtree *node)
{
	if (!(*node))
		return ;
	_bt_clear(&(*node)->left);
	_bt_clear(&(*node)->right);
	_cmd_clear(&(*node)->cmd_line);
	free((*node));
	(*node) = NULL;
}
