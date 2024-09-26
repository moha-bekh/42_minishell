/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _path_slasher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 02:37:18 by oek               #+#    #+#             */
/*   Updated: 2024/09/26 02:37:22 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_path_slasher(t_pdata data)
{
	char	**path;
	char	*tmp;
	int		i;

	if (data->args.env_path)
		path = data->args.env_path;
	else
		path = data->args.hard_path;
	i = -1;
	while (path[++i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
			return (_FAILURE);
		free(tmp);
		tmp = NULL;
	}
	return (_SUCCESS);
}
