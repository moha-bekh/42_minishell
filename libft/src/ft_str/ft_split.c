/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:16:28 by moha              #+#    #+#             */
/*   Updated: 2024/07/26 16:32:59 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, int c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**init_arr(int count)
{
	char	**arr;

	arr = ft_calloc((count + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	arr[count] = 0;
	return (arr);
}

bool	splitter(char const *str, char c, char **arr, bool show_sep)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c && !ft_isspace(str[i]))
		{
			if (i > 0 && show_sep)
				start = i - 1;
			else
				start = i;
			while (str[i] && str[i] != c)
				i++;
			arr[j] = ft_substr(str, start, (i - start));
			if (!arr[j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

char	**ft_split(char const *str, char c, bool show_sep)
{
	char	**arr;

	if (!str || !c)
		return (NULL);
	arr = init_arr(count_word(str, c));
	if (!arr)
		return (NULL);
	if (!splitter(str, c, arr, show_sep))
		return (ft_free_arr(arr), NULL);
	return (arr);
}
