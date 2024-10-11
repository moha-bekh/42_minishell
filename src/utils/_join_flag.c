/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _join_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:30:24 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/11 16:30:47 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_join_flag(t_pdata data, int i)
{
	if (data->prompt[i] && !ft_isspace(data->prompt[i]))
		data->tokens->d_bot->flag = true;
	else
		data->tokens->d_bot->flag = false;
}
