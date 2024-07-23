/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:22:01 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 19:22:55 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env_print(u_padll dll)
{
	t_pev	tmp;

	tmp = dll->e_top;
	while (tmp)
	{
		printf("\033[0;34m");
		printf("%s=%s", tmp->key, tmp->value);
		printf("\033[0;39m\n");
		tmp = tmp->next;
	}
}
