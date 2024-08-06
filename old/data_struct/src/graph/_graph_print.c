/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _graph_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:04:15 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 18:44:58 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_graph_print(t_pgraph graph)
{
	t_pgnode	node;
	int			i;

	if (!graph)
		return ;
	i = -1;
	while (++i < graph->vertices)
	{
		node = graph->adjlist[i].top;
		printf("%d: ", i);
		while (node)
		{
			printf("%d ", node->value);
			node = node->next;
		}
		printf("NULL\n");
	}
	return ;
}
