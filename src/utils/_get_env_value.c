/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_env_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 02:39:25 by oek               #+#    #+#             */
/*   Updated: 2024/10/23 02:52:55 by mbekheir         ###   ########.fr       */
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
	if (!ft_strcmp(key, "PATH") && data->args._hard_path)
		return (data->args._hard_path);
	return (NULL);
}
