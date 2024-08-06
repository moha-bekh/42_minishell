/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _alloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:30:53 by moha              #+#    #+#             */
/*   Updated: 2024/07/30 10:07:36 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

int _alloc(void **target, size_t size)
{
	if (!size)
		return (EXIT_FAILURE);
	(*target) = malloc(size);
	if (!(*target))
		return (EXIT_FAILURE);
	ft_memset((*target), 0, size);
	return (EXIT_SUCCESS);
}
