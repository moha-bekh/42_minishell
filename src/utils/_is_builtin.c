/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _is_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:32:45 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/26 12:32:51 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_is_builtin(t_pdata data, char **args)
{
	t_pnlst	tmp;

	if (!args || !args[0])
		return (0);
	tmp = data->builtins->d_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->addr_1, args[0]))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
