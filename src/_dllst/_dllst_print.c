/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dllst_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:32:49 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/27 01:39:44 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_dllst_print_builtins(u_padllst dllst)
{
	char	*str;
	t_pnlst	tmp;

	if (!dllst)
		return ;
	printf("\n");
	tmp = dllst->d_top;
	while (tmp)
	{
		str = (char *)tmp->addr_1;
		if (str)
			printf("%s\n", str);
		tmp = tmp->next;
	}
	printf("\n");
}

void	_dllst_print_env(u_padllst dllst)
{
	char	*str;
	t_pnlst	tmp;

	if (!dllst)
		return ;
	tmp = dllst->d_top;
	while (tmp)
	{
		str = (char *)tmp->addr_2;
		if (*str)
			printf("%s=%s\n", (char *)tmp->addr_1, str);
		tmp = tmp->next;
	}
	printf("\n");
}

void	_dllst_print_export(u_padllst dllst)
{
	char	*str;
	t_pnlst	tmp;

	if (!dllst)
		return ;
	tmp = dllst->d_top;
	while (tmp)
	{
		str = (char *)tmp->addr_2;
		if (*str)
			printf("export %s=\"%s\"\n", (char *)tmp->addr_1, str);
		else
			printf("export %s\n", (char *)tmp->addr_1);
		tmp = tmp->next;
	}
	printf("\n");
}

void	_dllst_print_tokens(u_padllst dllst)
{
	t_pnlst	tmp;

	if (!dllst)
		return ;
	printf("size: %d\n", dllst->d_size);
	tmp = dllst->d_top;
	while (tmp)
	{
		printf("type: %c \t", tmp->x);
		printf("join: %d\t", tmp->flag);
		printf("value: %s \n", (char *)tmp->addr_1);
		tmp = tmp->next;
	}
	printf("\n");
}
