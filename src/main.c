/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:00:00 by moha              #+#    #+#             */
/*   Updated: 2024/08/07 13:56:44 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_skip(char *input)
{
	if (!*input)
		return (_IS);
	if (!ft_strncmp(input, "\n", 1))
		return (_IS);
	if (!ft_strncmp(input, "clear", 5))
	{
		system("clear");
		return (_IS);
	}
	return (_NOT);
}

int	main(int ac, char **av, char **ev)
{
	t_data	data;
	int		ret;

	if (_data_init(&data, ac, av, ev))
		return (_data_cleaner(&data), _FAILURE);
	while (1)
	{
		data.input = readline(">$ ");
		if (!data.input)
			return (_data_cleaner(&data), _FAILURE);
		add_history(data.input);
		if (_skip(data.input))
		{
			_data_clear_lists(&data);
			continue ;
		}
		ret = _token(&data);
		if (ret > 0 && ret < 3)
			return (_data_cleaner(&data), _FAILURE);
		_expand(&data);
		// _tok_print(data.tok);
		data.tree = _tree(&data);
		_parsing(data.tree);
		_exec(&data, data.tree);
		// _op_bt_print(data.tree, true, 0);
		_data_clear_lists(&data);
	}
	return (_data_cleaner(&data), _SUCCESS);
}
