/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 08:06:02 by moha              #+#    #+#             */
/*   Updated: 2024/07/17 14:14:13 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_create(void *value)
{
	t_btree	*btree;

	btree = ft_calloc(1, sizeof(t_btree));
	if (!btree)
		return (NULL);
	btree->value = value;
	return (btree);
}

// void	create_res(t_btree **btree);
// create_res(&btree);
// void create_res(t_btree **btree)
// {
// 	ft_printf("=====================================\n"); // REMOVE
// 	ft_printf("CREATE btree ptr : %p\n", (*btree)); // REMOVE
// 	ft_printf("WITH value : %d\n", *(int *)(*btree)->value); // REMOVE
// 	return ;
// }
