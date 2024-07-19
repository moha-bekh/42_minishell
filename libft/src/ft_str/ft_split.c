/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:16:28 by moha              #+#    #+#             */
/*   Updated: 2024/07/16 22:29:47 by moha             ###   ########.fr       */
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

bool	splitter(char const *str, char c, char **arr)
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

char	**ft_split(char const *str, char c)
{
	char	**arr;

	if (!str || !c)
		return (NULL);
	arr = init_arr(count_word(str, c));
	if (!arr)
		return (NULL);
	if (!splitter(str, c, arr))
		return (m_free_arr(arr), NULL);
	return (arr);
}
