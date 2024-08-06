/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _graph_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:03:52 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 19:11:36 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pgraph	_graph_create(int vertices, bool sens)
{
	t_pgraph	graph;
	int			i;

	if (_alloc((void *)&graph, sizeof(*graph)))
		return (NULL);
	graph->sens = sens;
	graph->vertices = vertices;
	if (_alloc((void *)&graph->adjlist, vertices * sizeof(*graph->adjlist)))
		return (free(graph), NULL);
	i = -1;
	while (++i < vertices)
		graph->adjlist[i].top = NULL;
	if (sens)
		graph->graph_file = fopen("digraph.out", "w");
	else
		graph->graph_file = fopen("graph.out", "w");
	if (!graph->graph_file)
		return (printf("graph_file OPF"), free(graph->adjlist), free(graph),
			NULL);
	if (sens)
		fprintf(graph->graph_file, "digraph G\n{\n");
	else
		fprintf(graph->graph_file, "graph G\n{\n");
	return (graph);
}
