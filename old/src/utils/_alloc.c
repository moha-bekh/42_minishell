/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _alloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:30:53 by moha              #+#    #+#             */
/*   Updated: 2024/08/06 08:04:56 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_alloc(void **target, size_t size)
{
	if (!size)
		return (_FAILURE);
	(*target) = malloc(size);
	if (!(*target))
		return (_ALLOC);
	ft_memset((*target), 0, size);
	return (_SUCCESS);
}
