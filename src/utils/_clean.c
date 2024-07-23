/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _clean.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:33:55 by moha              #+#    #+#             */
/*   Updated: 2024/07/23 16:09:35 by mbekheir         ###   ########.fr       */
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

void	ft_free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
