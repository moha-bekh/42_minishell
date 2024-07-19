/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:55:55 by moha              #+#    #+#             */
/*   Updated: 2024/07/19 16:13:13 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	_unset(t_dll *env, char *key)
// {
// 	t_node	*tmp;
// 	int		i;

// 	tmp = env->top;
// 	i = -1;
// 	while (++i < env->size)
// 	{
// 		if (!ft_strcmp(tmp->key, key))
// 		{
// 			_dll_pop_in(env, tmp);
// 			return ;
// 		}
// 		tmp = tmp->next;
// 	}
// }
