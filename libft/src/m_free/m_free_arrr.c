/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_free_arrr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:51:48 by mbekheir          #+#    #+#             */
/*   Updated: 2024/05/15 17:03:14 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	m_free_arrr(char ***arrr)
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
			m_free(arrr[i][j]);
		m_free(arrr[i]);
	}
	m_free(arrr);
}
