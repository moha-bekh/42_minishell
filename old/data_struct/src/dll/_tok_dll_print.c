/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_dll_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:38:22 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 19:04:44 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

void	_tok_dll_print(t_pdll_tok dll)
{
	t_ptok	tmp;

	if (!dll)
		return (ft_putstr_fd("tokens is NULL\n", STDERR_FILENO));
	tmp = dll->top;
	while (tmp)
	{
		printf("\033[0;34m");
		printf("ptr : %p\t", tmp);
		printf("type : %c\t", tmp->type);
		printf("value : %s\t", tmp->value);
		printf("\033[0;39m\n");
		if (tmp->tokens)
			_tok_dll_print(tmp->tokens);
		tmp = tmp->next;
	}
	return ;
}
