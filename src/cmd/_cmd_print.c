/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:00:11 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/29 19:36:29 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_cmd_print(u_padll dll)
{
	t_pcmd	tmp;
	int		i;

	if (!dll)
		return ;
	tmp = dll->c_top;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd_a && tmp->cmd_a[++i])
		{
			printf(" %s ", tmp->cmd_a[i]);
			if (!tmp->cmd_a[i + 1] && tmp->next)
				printf("\n");
		}
		tmp = tmp->next;
	}
	return ;
}
