/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_foreach.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:49:45 by moha              #+#    #+#             */
/*   Updated: 2024/08/31 16:40:38 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_cmd_foreach(t_pdata data, t_pncmd cmd, int (*f)(t_pdata, t_pncmd),
		char *limiters)
{
	t_pncmd	tmp;

	tmp = cmd;
	while (tmp)
	{
		if (limiters && _tok_id(tmp->token->x, limiters))
			break ;
		if (f(data, tmp))
			return (_FAILURE);
		tmp = tmp->next;
	}
	return (_SUCCESS);
}