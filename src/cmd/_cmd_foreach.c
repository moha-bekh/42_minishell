/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_foreach.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:43:46 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/30 10:27:15 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_cmd_foreach(u_padll dll, void (*func)(t_pcmd))
{
	t_pcmd	tmp;

	if (!dll)
		return ;
	tmp = dll->c_top;
	while (tmp)
	{
		func(tmp);
		tmp = tmp->next;
	}
}
