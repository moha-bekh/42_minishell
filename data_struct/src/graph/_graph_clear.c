/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _graph_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:03:45 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 18:47:40 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_graph_clear(t_pgraph graph)
{
	t_pgnode	node;
	t_pgnode	tmp;
	int			i;

	if (!graph)
		return ;
	i = -1;
	if (graph->adjlist)
	{
		while (++i < graph->vertices)
		{
			node = graph->adjlist[i].top;
			while (node)
			{
				tmp = node;
				node = node->next;
				free(tmp);
			}
		}
		free(graph->adjlist);
	}
	fprintf(graph->graph_file, "}\n");
	fclose(graph->graph_file);
	free(graph);
	return ;
}
