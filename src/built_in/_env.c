/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:58 by moha              #+#    #+#             */
/*   Updated: 2024/08/24 14:13:54 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_env(t_pdata data, t_pcmd *cmd)
{
	if (!data || !data->env)
		return (_SUCCESS);
	if ((*cmd)->args[1])
	{
		ft_dprintf(2, "env: %s: No such file or directory\n", (*cmd)->args[1]);
		return (127);
	}
	_dllst_print_env(data->env);
	return (_SUCCESS);
}
