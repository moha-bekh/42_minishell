/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:20:06 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/10 00:30:45 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dll	*dll_clear(t_dll *dll)
{
	if (!dll)
	{
		ft_putstr_fd("dll_clear: dll is NULL\n", STDERR_FILENO);
		return (NULL);
	}
	while (dll)
		dll = dll_bot_pop(dll);
	return (NULL);
}
