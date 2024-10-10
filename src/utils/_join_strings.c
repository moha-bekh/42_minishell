/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _join_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:46:04 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/11 01:49:19 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_join_strings(t_ppnlst token)
{
	t_pnlst	tmp;
	char	*old;

	tmp = *token;
	while (tmp && tmp->x != _PIPE && !_tok_id(tmp->x, _TYP_SEP))
	{
		if (tmp->addr_1 && tmp->flag)
		{
			tmp = tmp->next;
			old = tmp->addr_1;
			tmp->addr_1 = ft_strjoin(tmp->prev->addr_1, tmp->addr_1);
			free(old);
			free(tmp->prev->addr_1);
			tmp->prev->addr_1 = NULL;
			continue ;
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}
