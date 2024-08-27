/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:01:58 by moha              #+#    #+#             */
/*   Updated: 2024/08/27 16:51:47 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_env(t_pdata data, t_ppncmd cmd)
{
	if (!data || !data->env)
		return (_SUCCESS);
	if ((*cmd)->args[1])
		return (_err_print(_ERR_ENV_NO_FILE, (*cmd)->args[1], true, 127));
	_dlst_print_env(data->env);
	return (_SUCCESS);
}
