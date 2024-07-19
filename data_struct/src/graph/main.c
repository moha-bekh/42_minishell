/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:04:23 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 18:48:09 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

int	main(void)
{
	t_pgraph	graph;

	graph = _graph_create(10, false);
	_graph_add_edge(graph, 0, 1);
	_graph_add_edge(graph, 0, 4);
	_graph_add_edge(graph, 0, 5);
	_graph_add_edge(graph, 0, 9);
	_graph_add_edge(graph, 7, 8);
	_graph_add_edge(graph, 3, 1);
	_graph_print(graph);
	_graph_clear(graph);
	// _greaph_display(graph);
	return (EXIT_SUCCESS);
}
