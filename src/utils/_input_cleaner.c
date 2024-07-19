/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _input_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:40:21 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/11 15:07:10 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_new_input_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && str[i] == _SPACE)
		i++;
	while (str[i] && str[i] != _NEWLINE)
	{
		if (str[i] && (str[i + 1] != _SPACE && str[i + 1] != _NEWLINE))
		{
			len++;
			i++;
		}
		else
			i++;
	}
	return (len);
}

int	_start_or_end(char *str, int i)
{
	if (i == 0)
	{
		while (str[i] && str[i] == _SPACE)
			i++;
	}
	else
	{
		while (str[i] && str[i] == _SPACE)
			i--;
	}
	return (i);
}

int	start_n_end(t_data *data)
{
	char	*old;
	char	*new;
	int		i;
	int		j;

	if (!data)
		return (EXIT_FAILURE);
	i = _start_or_end(data->blocs->bot->value, 0);
	j = _start_or_end(data->blocs->bot->value, ft_strlen(data->blocs->bot->value));
	old = ft_substr(data->blocs->bot->value, i, j);
	j = _new_input_len(old);
	if (_alloc((void *)&new, j + 2) || !new)
		return (EXIT_FAILURE);
	j = 0;
	i = -1;
	while (old[++i])
		new[i] = old[i];
	new[i] = _NEWLINE;
	new[++i] = '\0';
	free(old);
	free(data->blocs->bot->value);
	data->blocs->bot->value = new;
	printf("new input: %s\n", new);
	return (EXIT_SUCCESS);
}

int	_clean_input(t_data *data)
{
	// char	*old;
	// char	*new;
	// int		i;

	if (!data)
		return (EXIT_FAILURE);
	if (start_n_end(data))
		return (EXIT_FAILURE);
// 	old = data->blocs->bot->value;
// 	if (_alloc((void *)&new, ft_strlen(old) + 1) || !new)
// 		return (EXIT_FAILURE);
	// i = 0;
// 	while (old[i])
// 	{
// 		if (old[i] == _SQUOTE)
// 		{
// 			while (old[i] && old[i] != _SQUOTE)
// 			{
// 				new[i] = old[i];
// 				i++;
// 			}
// 		}
// 		else if (old[i] == _DQUOTE)
// 		{
// 			while (old[i] && old[i] != _DQUOTE)
// 			{
// 				new[i] = old[i];
// 				i++;
// 			}
// 		}
// 		else if (old[i] == _SPACE)
// 		{
// 			new[i] = old[i];
// 			while (old[i] && old[i] == _SPACE)
// 				i++;
// 		}
// 		else
// 		{
// 			new[i] = old[i];
// 			i++;
// 		}
// 	}
// 	printf("cleaned input: %s\n", new);
// 	free(data->blocs->bot->value);
// 	data->blocs->bot->value = new;
	return (EXIT_SUCCESS);
}
