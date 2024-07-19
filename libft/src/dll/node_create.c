/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:15:25 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/10 00:18:29 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*node_create(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		ft_putstr_fd("node_create: allocation failed\n", STDERR_FILENO);
		return (NULL);
	}
	ft_memset(node, 0, sizeof(t_node));
	return (node);
}
