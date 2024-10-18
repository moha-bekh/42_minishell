/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _check_patterns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:34:47 by mbekheir          #+#    #+#             */
/*   Updated: 2024/10/18 13:35:40 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_check_patterns(t_pnlst token, char **patt)
{
	char	*tmp;
	int		i;

	tmp = token->addr_1;
	i = 0;
	while (patt[i])
	{
		tmp = ft_strnstr(tmp, patt[i], ft_strlen(tmp));
		if (!tmp)
			return (false);
		tmp++;
		i++;
	}
	return (true);
}
