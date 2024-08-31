/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _alloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:43:55 by moha              #+#    #+#             */
/*   Updated: 2024/08/31 16:44:27 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	_alloc(void **target, size_t size)
{
	if (!size)
		return (EXIT_FAILURE);
	(*target) = malloc(size);
	if (!(*target))
		return (EXIT_FAILURE);
	ft_memset((*target), 0, size);
	return (EXIT_SUCCESS);
}
