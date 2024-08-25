/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _slitu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 07:13:05 by moha              #+#    #+#             */
/*   Updated: 2024/08/08 09:48:47 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_join_strings(t_pdata data)
{
	t_ptok	tmp;
	t_ptok tmp2;
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
			tmp->next->value = ft_strjoin(tmp->value, ptr);
			free(ptr);
			ptr = NULL;
			tmp2 = tmp->next;
			data->tok = _tok_pop_in(data->tok, tmp);
			tmp = tmp2;
			continue ;
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}
