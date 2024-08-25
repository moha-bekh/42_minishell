/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_pop_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:36:15 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/07 18:36:13 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_tok_pop_back(u_padll dll)
{
	t_ptok	tmp;

	if (!dll)
		return (NULL);
	if ((dll->t_top && dll->t_bot) && dll->t_top == dll->t_bot)
	{
		free(dll->t_top->value);
		dll->t_top->value = NULL;
		free(dll->t_top);
		dll->t_top = NULL;
		free(dll);
		dll = NULL;
		return (NULL);
	}
	tmp = dll->t_bot;
	dll->t_bot = dll->t_bot->prev;
	dll->t_bot->next = NULL;
	tmp->prev = NULL;
	free(tmp->value);
	tmp->value = NULL;
	free(tmp);
	tmp = NULL;
	dll->t_size--;
	return (dll);
}
