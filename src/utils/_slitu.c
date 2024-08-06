/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _slitu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 07:13:05 by moha              #+#    #+#             */
/*   Updated: 2024/08/06 07:13:20 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_path_slash(t_pdata data, int idx)
{
	int	i;

	if (!data || !data->paths[idx])
		return (_ERROR);
	i = -1;
	while (data->paths[idx][++i])
	{
		data->tmp = data->paths[idx][i];
		data->paths[idx][i] = ft_strjoin(data->paths[idx][i], "/");
		free(data->tmp);
	}
	return (_SUCCESS);
}

int	_is_path(char *str)
{
	if (!str)
		return (_ERROR);
	if (ft_strchr(str, '/'))
		return (_IS);
	return (_NOT);
}
