/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _blc_dll_push_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:38:28 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 21:29:40 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pdll_blc	_blc_dll_push_back(t_pdll_blc dll, char *value)
{
	t_pblc	node;

	if (_alloc((void *)&node, sizeof(t_blc)) || !node)
		return (ft_putstr_fd(ALLOC_FAIL, STDERR_FILENO), NULL);
	node->next = NULL;
	node->prev = NULL;
	node->blocs = NULL;
	if (!dll)
	{
		if (_alloc((void *)&dll, sizeof(t_dll_blc)) || !dll)
			return (ft_putstr_fd(ALLOC_FAIL, STDERR_FILENO), NULL);
		dll->top = node;
		dll->bot = node;
	}
	else
	{
		node->prev = dll->bot;
		dll->bot->next = node;
		dll->bot = node;
	}
	node->value = value;
	dll->size++;
	return (dll);
}
