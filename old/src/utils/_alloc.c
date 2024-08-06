/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _alloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:30:53 by moha              #+#    #+#             */
/*   Updated: 2024/07/30 10:09:05 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_alloc(void **target, size_t size)
{
	if (!size)
		return (_EMPTY);
	(*target) = malloc(size);
	if (!(*target))
		return (_ALLOC);
	ft_memset((*target), 0, size);
	return (_SUCCESS);
}
