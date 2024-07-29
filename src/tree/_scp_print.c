/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _scp_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:58:44 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/29 11:37:26 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_scp_print(u_padll dll)
{
	t_pscop	tmp;

	if (!dll)
		return ;
	tmp = dll->s_top;
	while (tmp)
	{
		printf("\033[0;34m");
		printf("ptr_op: %p\t", tmp->ptr_op);
		printf("type: %c\t", tmp->ptr_op->type);
		// printf("status: %d\t", tmp->ptr_op->status);
		printf("\033[0;39m\n");
		tmp = tmp->next;
	}
	return ;
}
