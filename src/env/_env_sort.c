/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:32:05 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/23 21:03:10 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_env_sort(u_padll dll)
{
	t_pev	node;
	int		i;

	if (!dll)
		return (NULL);
	i = -1;
	while (++i < dll->e_size)
	{
		node = dll->e_top;
		while (node)
		{
			if (node->next && ft_strcmp(node->key, node->next->key) > 0)
			{
				ft_memswap(node->key, node->next->key, sizeof(char *));
				ft_memswap(node->value, node->next->value, sizeof(char *));
			}
			node = node->next;
		}
	}
	return (dll);
}
