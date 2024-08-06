/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _node_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:04:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 19:11:06 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pgnode	_node_add(int value)
{
	t_pgnode	node;

	if (_alloc((void *)&node, sizeof(*node)))
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}
