/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:26:31 by moha              #+#    #+#             */
/*   Updated: 2024/07/12 12:23:45 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	btree_size(t_btree *btree)
{
	if (!btree)
		return (0);
	return (1 + btree_size(btree->left) + btree_size(btree->right));
}
