/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dll_print_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:06:20 by moha              #+#    #+#             */
/*   Updated: 2024/07/18 19:13:21 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_dll_print_env(t_pdll dll)
{
	t_pnode	tmp;
	int		i;

	if (!dll)
		return ;
	tmp = dll->top;
	i = -1;
	while (++i < dll->size)
	{
		if (tmp->key)
			printf("%s=", tmp->key);
		if (tmp->value)
			printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
	return ;
}
