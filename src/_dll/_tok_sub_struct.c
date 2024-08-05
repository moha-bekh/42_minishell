/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_sub_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:49:21 by moha              #+#    #+#             */
/*   Updated: 2024/07/20 21:26:10 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_tok_sub_struct(t_ptok start, t_ptok end)
{
	u_padll	new_dll;

	if (!start || !end)
		return (NULL);
	new_dll = NULL;
	if (_alloc((void *)&new_dll, sizeof(u_adll)) || !new_dll)
		return (NULL);
	new_dll->t_top = start;
	new_dll->t_bot = end;
	return (new_dll);
}
