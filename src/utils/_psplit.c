/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _psplit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:58:27 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/26 18:38:28 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_is_sep(char c, char *sep)
{
	int	i;

	i = -1;
	while (sep[++i])
	{
		if (c == sep[i])
			return (1);
	}
	return (0);
}

int	_cnt_chr(char *str, char *sep, int **tab)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	while (_is_sep(str[i], sep))
		i++;
	j = 1;
	while (str[i])
	{
		if (str[i] && !_is_sep(str[i], sep))
		{
			cnt = 0;
			while (str[i] && !_is_sep(str[i], sep))
			{
				cnt++;
				i++;
			}
			(*tab)[j++] = cnt;
		}
		else
			i++;
	}
	(*tab)[0] = j - 1;
	return ((*tab)[0]);
}

char	**_psplit(char *str, char *sep)
{
	char	**arr;
	int		*tab;
	int		k;
	int		i;
	int		j;

	if (_alloc((void *)&tab, sizeof(int) * ft_strlen(str)) || !tab)
		return (NULL);
	if (_alloc((void *)&arr, 8 * (_cnt_chr(str, sep, &tab) + 1)) || !arr)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < tab[0])
	{
		k = 0;
		if (_alloc((void *)&arr[i], sizeof(char) * (tab[i + 1] + 2)) || !arr[i])
			return (free(tab), ft_free_arr(arr), NULL);
		while (str[j] && _is_sep(str[j], sep))
			arr[i][k++] = str[j++];
		while (str[j] && !_is_sep(str[j], sep))
			arr[i][k++] = str[j++];
		arr[i][k] = 0;
	}
	return (free(tab), arr);
}
