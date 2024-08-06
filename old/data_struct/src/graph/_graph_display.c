/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _graph_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:04:09 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 18:44:31 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_graph_display(t_pgraph graph)
{
	if (!graph)
		return ;
	if (graph->sens)
		system("dot -Tpng graph.out -o graph.png");
	else
		system("dot -Tpng digraph.out -o graph.png");
	return ;
}
