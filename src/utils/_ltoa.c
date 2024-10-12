/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ltoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:10:26 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/12 10:10:47 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**_ltoa(t_padlst dlst)
{
	char	**arr;
	char	*pmt;
	int		i;
	t_pnlst	tmp;

	if (_alloc((void *)&arr, sizeof(char *) * (dlst->d_size + 1)) || !arr)
		return (NULL);
	tmp = dlst->d_top;
	i = 0;
	while (tmp)
	{
		pmt = ft_strjoin(tmp->addr_1, "=");
		if (!pmt)
			return (NULL);
		arr[i] = ft_strjoin(pmt, tmp->addr_2);
		free(pmt);
		pmt = NULL;
		if (!arr[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	return (arr);
}
