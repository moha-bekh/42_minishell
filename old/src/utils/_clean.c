/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _clean.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:33:55 by moha              #+#    #+#             */
/*   Updated: 2024/07/23 22:36:08 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_clean(void *target, size_t size)
{
	if (!target || !size)
		return ;
	ft_memset(target, 0, size);
	free(target);
	target = NULL;
	return ;
}
