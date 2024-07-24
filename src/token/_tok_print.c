/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:45:05 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/24 19:08:33 by mbekheir         ###   ########.fr       */
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
		printf("join: %d \t", tmp->join);
		printf("\033[0;39m\n");
		tmp = tmp->next;
	}
	return ;
}
