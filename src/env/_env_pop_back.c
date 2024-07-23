/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_pop_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:05:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 19:11:00 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_env_free(u_padll dll)
{
	t_pev	tmp;

	tmp = dll->e_bot;
	dll->e_bot = dll->e_bot->prev;
	dll->e_bot->next = NULL;
	free(tmp->key);
	tmp->key = NULL;
	free(tmp->value);
	tmp->value = NULL;
	tmp->prev = NULL;
	free(tmp);
	tmp = NULL;
	return (dll);
}

u_padll	_env_pop_back(u_padll dll)
{
	if (!dll)
		return (NULL);
	if ((dll->e_top && dll->e_bot) && dll->e_top == dll->e_bot)
	{
		free(dll->e_top->key);
		dll->e_top->key = NULL;
		free(dll->e_top->value);
		dll->e_top->value = NULL;
		free(dll->e_top);
		dll->e_top = NULL;
		free(dll);
		dll = NULL;
		return (NULL);
	}
	dll->e_size--;
	dll = _env_free(dll);
	return (dll);
}
