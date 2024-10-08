/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ltoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:10:26 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/04 11:54:26 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**_ltoa(t_padlst dlst)
{
	char	**arr;
	t_pnlst	tmp;
	int		i;

	if (_alloc((void *)&arr, sizeof(char *) * (dlst->d_size + 1)) || !arr)
		return (NULL);
	tmp = dlst->d_top;
	i = 0;
	while (tmp)
	{
		arr[i++] = ft_strdup(tmp->addr_1);
		if (!arr[i])
			return (NULL);
		tmp = tmp->next;
	}
	return (arr);
}
