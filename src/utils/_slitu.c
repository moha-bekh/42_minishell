/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _slitu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 07:13:05 by moha              #+#    #+#             */
/*   Updated: 2024/08/07 16:53:57 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_join_strings(t_pdata data)
{
	t_ptok	tmp;
	char	*ptr;

	if (!data || !data->tok)
		return (_FAILURE);
	ptr = NULL;
	tmp = data->tok->t_top;
	while (tmp)
	{
		if (tmp->join && tmp->next)
		{
			ptr = tmp->next->value;
			tmp->next->value = ft_strjoin(tmp->value, tmp->next->value);
			free(ptr);
			ptr = NULL;
			tmp = tmp->next;
			data->tok = _tok_pop_in(data->tok, tmp->prev);
			continue ;
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}
