/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dlst_foreach.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:49:45 by moha              #+#    #+#             */
/*   Updated: 2024/08/28 13:54:32 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_dlst_foreach(t_ppadlst dlst, void (*f)(t_pnlst), char *limiter)
{
	t_pnlst	tmp;

	tmp = (*dlst)->d_top;
	while (tmp)
	{
		if (tmp == limit)
			break ;
		f(tmp);
		tmp = tmp->next;
	}
}
