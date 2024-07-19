/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tok_dll_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:38:33 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/18 21:34:10 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_struct.h"

t_pdll_tok _tok_dll_clear(t_pdll_tok dll)
{
	if (!dll)
		return (ft_putstr_fd("tokens is NULL\n", STDERR_FILENO), NULL);
	while (dll)
	{
		if (dll->bot->tokens)
			dll->bot->tokens = _tok_dll_clear(dll->bot->tokens);
		dll = _tok_dll_pop_back(dll);
	}
	return (NULL);
}
