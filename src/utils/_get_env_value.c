/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_env_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 02:39:25 by oek               #+#    #+#             */
/*   Updated: 2024/09/26 02:39:54 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*_get_env_value(t_pdata data, char *key)
{
	t_pnlst	tmp;

	tmp = data->env->d_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->addr_1, key))
			return ((char *)tmp->addr_2);
		tmp = tmp->next;
	}
	return (NULL);
}
