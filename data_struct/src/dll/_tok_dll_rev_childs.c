/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_dll_rev_childs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:25:28 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 19:04:14 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pdll_tok	_tok_dll_rev_childs(t_pdll_tok dll)
{
	t_pdll_tok	t_ptrs[128];
	char		*v_ptrs[128];
	t_ptok		tmp;
	int			i;

	if (!dll)
		return (ft_putstr_fd("tokens is NULL\n", STDERR_FILENO), NULL);
	tmp = dll->top;
	i = -1;
	while (tmp)
	{
		if (tmp->tokens)
		{
			v_ptrs[++i] = tmp->value;
			t_ptrs[i] = tmp->tokens;
		}
		tmp = tmp->next;
	}
	tmp = dll->top;
	while (tmp)
	{
		if (tmp->tokens)
		{
			tmp->value = v_ptrs[i];
			tmp->tokens = t_ptrs[i--];
		}
		tmp = tmp->next;
	}
	return (dll);
}
