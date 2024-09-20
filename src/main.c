/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:00:00 by moha              #+#    #+#             */
/*   Updated: 2024/09/20 02:35:34 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_set_shell(t_pdata data)
{
	// struct termios	base_term;
	// struct termios new_term;

	if (_set_signals(data))
		return (_FAILURE);

	// if (isatty(STDIN_FILENO))
	// {
	// 	tcgetattr(STDIN_FILENO, &base_term);
	// 	new_term = base_term;
	// 	new_term.c_lflag &= ~(ICANON | ECHO);
	// 	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	// }
	return (_SUCCESS);
}


int	main(int ac, char **av, char **ev)
{
	static t_data	data;

	if (_data_init(&data, ac, av, ev) || _set_shell(&data))
		return (_data_clear(&data), _FAILURE);
	while (true)
	{
		data.prompt = readline(">$ ");
		if ((!data.prompt || !data.prompt[0]) && !_data_structs_clear(&data))
			continue ;
		add_history(data.prompt);
		if (_tok_list(&data) && !_data_structs_clear(&data))
			continue ;
		_tree_builder(&data.tree, data.tokens->d_top);
		if (_exec(&data, &data.tree) && !_data_structs_clear(&data))
			continue ;
		_data_structs_clear(&data);
	}
	return (_data_clear(&data), _SUCCESS);
}
