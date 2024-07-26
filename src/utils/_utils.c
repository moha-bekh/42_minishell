/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:35:57 by moha              #+#    #+#             */
/*   Updated: 2024/07/26 18:41:24 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_free_arr(char **arr)
// {
// 	int	i;

// 	if (!arr)
// 		return ;
// 	i = -1;
// 	while (arr[++i])
// 		free(arr[i]);
// 	free(arr);
// }

int	_get_start_index(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			return (i);
	}
	return (i);
}

char	*_get_env_value(u_padll env, char *key)
{
	t_pev	tmp;

	tmp = env->e_top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
