/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _scp_pop_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:57:18 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 19:24:44 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll _scp_pop_back(u_padll dll)
{
	t_pscop tmp;
	if (!dll)
		return (NULL);
	if ((dll->s_top && dll->s_bot) && dll->s_top == dll->s_bot)
	{
		// free(dll->s_top->ptr_op);
		// dll->s_top->ptr_op = NULL;
		free(dll->s_top);
		dll->s_top = NULL;
		free(dll);
		dll = NULL;
		return (NULL);
	}
	tmp = dll->s_bot;
	dll->s_bot = dll->s_bot->prev;
	dll->s_bot->next = NULL;
	// free(tmp->ptr_op);
	// tmp->ptr_op = NULL;
	tmp->prev = NULL;
	free(tmp);
	tmp = NULL;
	dll->s_size--;
	return (dll);
}
