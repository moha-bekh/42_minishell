/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _graph_add_edge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:03:40 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 18:43:26 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_graph_add_edge(t_pgraph graph, int src, int dst)
{
	t_pgnode	node;

	if (!graph)
		return ;
	node = _node_add(dst);
	node->next = graph->adjlist[src].top;
	graph->adjlist[src].top = node;
	if (!graph->sens)
	{
		node = _node_add(src);
		node->next = graph->adjlist[dst].top;
		graph->adjlist[dst].top = node;
	}
	if (graph->sens)
		fprintf(graph->graph_file, "\t%d -> %d;\n", src, dst);
	else
		fprintf(graph->graph_file, "\t%d -- %d;\n", src, dst);
	return ;
}
