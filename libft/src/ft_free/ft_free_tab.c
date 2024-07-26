/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_free_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:20:11 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/26 16:29:26 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(int **tab, int size)
{
	int	i;

	if (!tab || size < 1)
		return ;
	i = -1;
	while (++i < size)
		ft_free(&tab[i]);
	ft_free(tab);
}
