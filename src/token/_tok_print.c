/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:45:05 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 20:10:37 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_tok_print(u_padll dll)
{
	t_ptok	tmp;

	if (!dll)
		return ;
	tmp = dll->t_top;
	while (tmp)
	{
		printf("\033[0;34m");
		printf("type: %c \t", tmp->type);
		printf("value: %s \t", tmp->value);
		printf("\033[0;39m\n");
		tmp = tmp->next;
	}
	return ;
}
