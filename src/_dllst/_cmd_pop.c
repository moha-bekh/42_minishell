/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:57:58 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/24 02:35:34 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_cmd_pop_back(u_padllst *dllst)
{
	t_pcmd	tmp;

	if (!*dllst)
		return ;
	tmp = (*dllst)->c_bot;
	(*dllst)->c_size--;
	if ((*dllst)->c_size)
	{
		tmp = (*dllst)->c_bot;
		(*dllst)->c_bot = (*dllst)->c_bot->prev;
		(*dllst)->c_bot->next = NULL;
	}
	free(tmp->path);
	ft_free_arr(tmp->args);
	free(tmp->redirs.here_name);
	*tmp = (t_cmd){0};
	free(tmp);
	tmp = NULL;
	if (!(*dllst)->c_size)
	{
		(**dllst) = (u_adllst){0};
		free(*dllst);
		*dllst = NULL;
	}
}

void	_cmd_clear(u_padllst *dllst)
{
	if (!*dllst)
		return ;
	while ((*dllst) && (*dllst)->c_size)
		_cmd_pop_back(dllst);
}
