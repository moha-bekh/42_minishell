/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_top_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:16:54 by mbekheir          #+#    #+#             */
/*   Updated: 2024/05/31 09:03:02 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*dll_top_value(t_dll *dll)
{
	if (dll_empty(dll))
	{
		ft_printf("dll empty\n");
		return (NULL);
	}
	return (dll->top->value);
}
