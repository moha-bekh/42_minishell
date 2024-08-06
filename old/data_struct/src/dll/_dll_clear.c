/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dll_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:59:49 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 21:30:12 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pdll	_dll_clear(t_pdll dll)
{
	if (!dll)
		return (ft_putstr_fd("dll is NULL\n", STDERR_FILENO), NULL);
	while (dll)
		dll = _dll_pop_back(dll);
	return (NULL);
}
