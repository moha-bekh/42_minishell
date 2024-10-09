/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:57:58 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/09 15:03:12 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	_cmd_pop_back(t_ppadlst dlst)
{
	t_pncmd	tmp;

	if (!*dlst)
		return ;
	tmp = (*dlst)->c_bot;
	(*dlst)->c_size--;
	if ((*dlst)->c_size)
	{
		tmp = (*dlst)->c_bot;
		(*dlst)->c_bot = (*dlst)->c_bot->prev;
		(*dlst)->c_bot->next = NULL;
	}
	free(tmp->path);
	ft_free_arr(tmp->args);
	// ft_free_arr(tmp->redirs.here_names);
	// free(tmp->redirs.here_limit);
	*tmp = (t_ncmd){0};
	free(tmp);
	tmp = NULL;
	if (!(*dlst)->c_size)
	{
		(**dlst) = (t_adlst){0};
		free(*dlst);
		*dlst = NULL;
	}
}

void	_cmd_clear(t_ppadlst dlst)
{
	if (!*dlst)
		return ;
	while ((*dlst) && (*dlst)->c_size)
		_cmd_pop_back(dlst);
}
