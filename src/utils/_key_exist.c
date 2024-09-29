/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _key_exist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:51:01 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/27 14:10:16 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_key_exist(t_padlst env, char *arg)
{
	t_pnlst	tmp;
	char	*key;

	key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	if (!key)
		return (_FAILURE);
	tmp = env->d_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->addr_1, key))
		{
			free(key);
			return (true);
		}
		tmp = tmp->next;
	}
	free(key);
	return (false);
}
