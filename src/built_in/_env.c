/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alblanc <alblanc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 02:56:56 by alblanc           #+#    #+#             */
/*   Updated: 2024/10/23 16:03:26 by alblanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_env(t_pdata data, char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "env"))
			return (_err_print(_ERR_ENV_NO_FILE, args[i], true, 127));
	}
	_dlst_print_env(data->env);
	return (_SUCCESS);
}
