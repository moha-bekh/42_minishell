/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:14:51 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/10 00:16:50 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dll	*dll_create(void)
{
	t_dll	*dll;

	dll = malloc(sizeof(t_dll));
	if (!dll)
	{
		ft_putstr_fd("dll_creaate: allocation failed\n", STDERR_FILENO);
		return (NULL);
	}
	ft_memset(dll, 0, sizeof(t_dll));
	return (dll);
}
