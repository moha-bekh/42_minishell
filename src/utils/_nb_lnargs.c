/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _nb_lnargs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 02:34:44 by oek               #+#    #+#             */
/*   Updated: 2024/09/26 02:34:48 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_nb_lnargs(t_pnlst token)
{
	t_pnlst	tmp;
	int		i;

	if (!token)
		return (0);
	tmp = token;
	i = 0;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (tmp && _tok_id(tmp->x, _TYP_REDIRS))
		{
			tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
			continue ;
		}
		i++;
		tmp = tmp->next;
	}
	return (i);
}
