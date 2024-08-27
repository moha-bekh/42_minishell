/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _dlst_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:32:49 by mbekheir          #+#    #+#             */
/*   Updated: 2024/08/27 16:38:07 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_dlst_print_builtins(t_padlst dlst)
{
	char	*str;
	t_pnlst	tmp;

	if (!dlst)
		return ;
	printf("\n");
	tmp = dlst->d_top;
	while (tmp)
	{
		str = (char *)tmp->addr_1;
		if (str)
			printf("%s\n", str);
		tmp = tmp->next;
	}
	printf("\n");
}

void	_dlst_print_env(t_padlst dlst)
{
	char	*str;
	t_pnlst	tmp;

	if (!dlst)
		return ;
	tmp = dlst->d_top;
	while (tmp)
	{
		str = (char *)tmp->addr_2;
		if (*str)
			printf("%s=%s\n", (char *)tmp->addr_1, str);
		tmp = tmp->next;
	}
	printf("\n");
}

void	_dlst_print_export(t_padlst dlst)
{
	char	*str;
	t_pnlst	tmp;

	if (!dlst)
		return ;
	tmp = dlst->d_top;
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

void	_dlst_print_tokens(t_padlst dlst)
{
	t_pnlst	tmp;

	if (!dlst)
		return ;
	printf("size: %d\n", dlst->d_size);
	tmp = dlst->d_top;
	while (tmp)
	{
		printf("type: %c \t", tmp->x);
		printf("join: %d\t", tmp->flag);
		printf("value: %s \n", (char *)tmp->addr_1);
		tmp = tmp->next;
	}
	printf("\n");
}
