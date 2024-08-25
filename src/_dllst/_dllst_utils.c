/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dllst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:32:36 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/23 12:32:38 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_dllst_clear(u_padllst *dllst)
{
	while (*dllst)
		_dllst_pop_back(dllst);
}
