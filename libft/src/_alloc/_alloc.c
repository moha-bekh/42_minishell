/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _alloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:43:55 by moha              #+#    #+#             */
/*   Updated: 2024/09/21 00:55:28 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	_alloc(void **target, size_t size)
{
	if (!size)
		return (EXIT_FAILURE);
	(*target) = malloc(size);
	if (!(*target))
	{
		perror("malloc");
		return (EXIT_FAILURE);
	}
	ft_memset((*target), 0, size);
	return (EXIT_SUCCESS);
}
