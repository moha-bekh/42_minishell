/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:19:47 by mbekheir          #+#    #+#             */
/*   Updated: 2024/05/31 09:03:33 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dll_ptr(t_dll *dll)
{
	t_node	*tmp;
	int		i;

	if (dll_empty(dll) || dll->size == 0)
	{
		ft_printf("Nothing to print, dll empty\n");
		return ;
	}
	tmp = dll->top;
	i = 0;
	ft_printf("Total size: %d\n", dll->size);
	while (i < dll->size)
	{
		ft_printf("ptr [%d]: %p\n", i, (void *)tmp->value);
		tmp = tmp->next;
		i++;
	}
	return ;
}

void	dll_int(t_dll *dll)
{
	t_node	*tmp;
	int		i;

	if (dll_empty(dll) || dll->size == 0)
	{
		ft_printf("Nothing to print, dll empty\n");
		return ;
	}
	tmp = dll->top;
	i = 0;
	while (i < dll->size)
	{
		ft_printf("ptr : %p | [%d] v : %d | i : %d\n", tmp->value, i,
			*(int *)tmp->value, tmp->index);
		tmp = tmp->next;
		i++;
	}
	return ;
}

void	dll_str(t_dll *dll)
{
	t_node	*tmp;
	int		i;

	if (dll_empty(dll) || dll->size == 0)
	{
		ft_printf("Nothing to print, dll empty\n");
		return ;
	}
	tmp = dll->top;
	i = 0;
	ft_printf("Total size: %d\n", dll->size);
	while (i < dll->size)
	{
		ft_printf("ptr : %p | [%d] v : %s | i : %d\n", tmp->value, i,
			(char *)tmp->value, tmp->index);
		i++;
	}
	return ;
}

void	dll_char(t_dll *dll)
{
	t_node	*tmp;
	int		i;

	if (dll_empty(dll) || dll->size == 0)
	{
		ft_printf("Nothing to print, dll empty\n");
		return ;
	}
	tmp = dll->top;
	i = 0;
	ft_printf("Total size: %d\n", dll->size);
	while (i < dll->size)
	{
		ft_printf("ptr : %p | [%d] v : %c | i : %d\n", tmp->value, i,
			(char *)tmp->value, tmp->index);
		tmp = tmp->next;
		i++;
	}
	return ;
}

void	dll_print(t_dll *dll, void (*print)(t_dll *))
{
	if (!dll || !print)
	{
		ft_printf("Nothing to print, dll empty\n");
		return ;
	}
	return (print(dll));
}
