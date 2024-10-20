/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:15:47 by oek               #+#    #+#             */
/*   Updated: 2024/10/21 00:15:52 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *_get_path(t_pdata data)
{
	t_pnlst tmp;

	tmp = data->env->d_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->addr_1, "PATH"))
			return (tmp->addr_2);
		tmp = tmp->next;
	}
	return (NULL);
}
