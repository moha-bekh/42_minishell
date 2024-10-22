/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _join_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:46:04 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/22 13:29:47 by mbekheir         ###   ########.fr       */
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
			if (!tmp->addr_1)
				tmp->addr_1 = ft_strdup(tmp->prev->addr_1);
			else
			{
				old = tmp->addr_1;
				tmp->addr_1 = ft_strjoin(tmp->prev->addr_1, tmp->addr_1);
				free(old);
			}
			free(tmp->prev->addr_1);
			tmp->prev->addr_1 = NULL;
			continue ;
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}
