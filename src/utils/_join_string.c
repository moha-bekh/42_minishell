/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _join_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:13:04 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/11 18:03:24 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_join_string(t_ppnlst token)
{
	t_pnlst	tmp;
	char	*old_str;
	char	a;
	char	b;

	tmp = tmp->next;
	old_str = tmp->addr_1;
	tmp->addr_1 = ft_strjoin(tmp->prev->addr_1, tmp->addr_1);
	free(old_str);
	a = tmp->prev->x;
	b = tmp->x;
	old_str = tmp->addr_2;
	tmp->addr_2 = ft_strjoin(&a, &b);
	free(old_str);
	_dlst_pop_in(&(*token)->manager, &tmp->prev);
}
