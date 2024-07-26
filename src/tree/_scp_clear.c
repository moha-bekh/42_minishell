/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _scp_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:23:39 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 19:24:54 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_scp_clear(u_padll dll)
{
	if (!dll)
		return (NULL);
	while (dll)
		dll = _scp_pop_back(dll);
	return (NULL);
}
