/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dll_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:04:15 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 19:24:06 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_dll_print(t_pdll dll)
{
	t_pnode tmp;
	int		i;

	if (!dll)
		return (ft_putstr_fd("dll is NULL\n", STDERR_FILENO));
	tmp = dll->top;
	i = -1;
	while (++i < dll->size)
	{
		printf("\033[0;35mdll value : %s\033[0;39m\t", tmp->value);
		printf("\033[0;35mkey : %s\033[0;39m\n", tmp->key);
		tmp = tmp->next;
	}
	return ;
}
