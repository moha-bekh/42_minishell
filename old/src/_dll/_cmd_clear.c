/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:16:58 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/29 16:59:20 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_cmd_clear(u_padll dll)
{
	if (!dll)
		return (NULL);
	while (dll)
		dll = _cmd_pop_back(dll);
	return (NULL);
}
