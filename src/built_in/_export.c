/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:34:32 by moha              #+#    #+#             */
/*   Updated: 2024/07/19 16:13:20 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_dll	*_export(t_dll *dll, char **args)
// {
// 	int		i;
// 	char	**key_value;

// 	if (!args)
// 		return (_dll_print_env(dll), NULL);
// 	printf("args exist\n");
// 	i = 0;
// 	while (args[i])
// 	{
// 		if (args[i] && ft_strchr(args[i], '='))
// 		{
// 			key_value = ft_split(args[i], '=');
// 			if (!key_value)
// 				return (NULL);
// 			dll = _dll_push_back(dll, NULL);
// 			if (key_value[0])
// 				dll->bot->key = key_value[0];
// 			if (key_value[1])
// 				dll->bot->value = key_value[1];
// 		}
// 		i++;
// 	}
// 	_dll_print_env(dll);
// 	return (dll);
// }
