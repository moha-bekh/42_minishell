/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:22:01 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/24 17:31:35 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env_print(u_padll dll)
{
	t_pev	tmp;

	if (!dll)
		return ;
	tmp = dll->e_top;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return ;
}
