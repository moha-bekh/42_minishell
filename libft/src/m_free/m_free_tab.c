/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_free_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:20:11 by mbekheir          #+#    #+#             */
/*   Updated: 2024/05/15 16:54:02 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	m_free_tab(int **tab, int size)
{
	int	i;

	if (!tab || size < 1)
		return ;
	i = -1;
	while (++i < size)
		m_free(&tab[i]);
	m_free(tab);
}
