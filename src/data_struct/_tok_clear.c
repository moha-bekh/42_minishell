/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:38:10 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/19 18:39:37 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

u_padll	_tok_clear(u_padll dll)
{
	if (!dll)
		return (NULL);
	while (dll)
		dll = _tok_pop_back(dll);
	return (NULL);
}
