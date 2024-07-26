/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_free_arrr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:51:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/26 16:29:10 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_arrr(char ***arrr)
{
	int	i;
	int	j;

	if (!arrr)
		return ;
	i = -1;
	while (arrr[++i])
	{
		j = -1;
		while (arrr[i][++j])
			ft_free(arrr[i][j]);
		ft_free(arrr[i]);
	}
	ft_free(arrr);
}
