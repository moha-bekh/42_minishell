/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_wildcards_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:43:56 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/17 19:52:18 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_xpd_right_border(t_ppnlst token, t_ppadlst list)
{
	t_pnlst	tmp;
	char	*str;
	char	*rts;

	if (!*list)
		return (_SUCCESS);
	str = (*token)->addr_1;
	tmp = (*list)->d_top;
	while (tmp)
	{
		rts = tmp->addr_1;
		if (str[ft_strlen(str) - 1] != rts[ft_strlen(rts) - 1])
		{
			_dlst_pop_in(list, &tmp);
			if (*list)
				tmp = (*list)->d_top;
			else
				break ;
		}
		else
			tmp = tmp->next;
	}
	return (_SUCCESS);
}

int	_xpd_left_border(t_ppnlst token, t_ppadlst list)
{
	t_pnlst	tmp;
	char	*str;
	char	*rts;

	if (!*list)
		return (_SUCCESS);
	str = (*token)->addr_1;
	tmp = (*list)->d_top;
	while (tmp)
	{
		rts = tmp->addr_1;
		if (str[0] != rts[0])
		{
			_dlst_pop_in(list, &tmp);
			if (*list)
				tmp = (*list)->d_top;
			else
				break ;
		}
		else
			tmp = tmp->next;
	}
	return (_SUCCESS);
}
