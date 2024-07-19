/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_bot_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:17:14 by mbekheir          #+#    #+#             */
/*   Updated: 2024/05/31 08:59:51 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*dll_bot_value(t_dll *dll)
{
	if (dll_empty(dll))
	{
		ft_printf("dll empty\n");
		return (NULL);
	}
	return (dll->bot->value);
}
