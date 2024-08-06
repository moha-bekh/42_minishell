/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _blc_dll_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:38:22 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 21:27:27 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_blc_dll_print(t_pdll_blc dll)
{
	t_pblc	tmp;

	if (!dll)
		return (ft_putstr_fd("blocs is NULL\n", STDERR_FILENO));
	tmp = dll->top;
	while (tmp)
	{
		printf("\033[0;35mblocs prev : %p\033[0;39m \n", tmp->prev);
		printf("\tblocs value : %s\n", tmp->value);
		printf("\033[0;35mblocs next : %p\033[0;39m\n", tmp->next);
		if (tmp->blocs)
			_blc_dll_print(tmp->blocs);
		tmp = tmp->next;
	}
	return ;
}
