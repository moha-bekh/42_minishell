/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:51:13 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/21 10:51:17 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_get_paths_(t_pdata data, char ***paths)
{
	char	*tmp;

	*paths = NULL;
	tmp = _get_path(data);
	if (tmp)
	{
		*paths = ft_split(tmp, ':');
		if (!*paths)
			return (_FAILURE);
	}
	else if (!tmp && data->args._hard_path)
	{
		*paths = ft_split(data->args._hard_path, ':');
		if (!*paths)
			return (_FAILURE);
	}
	return (_SUCCESS);
}
