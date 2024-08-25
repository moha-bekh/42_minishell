/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 01:20:11 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/21 16:20:31 by mbekheir         ###   ########.fr       */
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
	{
		free(&tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}
