/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:05:47 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 19:58:32 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_env_clear(u_padll dll)
{
	if (!dll)
		return (NULL);
	while (dll)
		dll = _env_pop_back(dll);
	return (NULL);
}
