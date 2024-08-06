/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _blc_dll_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:38:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 21:26:01 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pdll_blc	_blc_dll_clear(t_pdll_blc dll)
{
	if (!dll)
		return (ft_putstr_fd("blocs is NULL\n", STDERR_FILENO), NULL);
	while (dll)
	{
		if (dll->bot->blocs)
			dll->bot->blocs = _blc_dll_clear(dll->bot->blocs);
		dll = _blc_dll_pop_back(dll);
	}
	return (NULL);
}
