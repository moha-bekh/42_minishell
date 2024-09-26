/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _xpd_wildcards_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:43:56 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/26 12:44:09 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_xpd_right_border(t_ppnlst token, t_ppadlst list)
{
	t_pnlst	tmp;
	char	*str;
	char	*rts;

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

int	_xpd_full_astrix(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '*')
			return (false);
		i++;
	}
	return (true);
}
