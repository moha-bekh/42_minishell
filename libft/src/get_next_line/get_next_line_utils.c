/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oek <oek@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:47:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/09/21 14:59:39 by oek              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_new_line(t_plist lst)
{
	t_plist	current;
	int		i;

	if (!lst)
		return (0);
	current = get_last_node(lst);
	i = 0;
	while (current->value[i])
	{
		if (current->value[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_plist	get_last_node(t_plist lst)
{
	t_plist current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	generate_line(t_plist lst, char **line)
{
	int	i;
	int	len;

	len = 0;
	if (!lst)
		return ;
	while (lst)
	{
		i = 0;
		while (lst->value[i])
		{
			if (lst->value[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		lst = lst->next;
	}
	*line = ft_calloc((len + 1), sizeof(char));
	if (!*line)
		return (free_list(&lst));
}

void	free_list(t_pplist lst)
{
	t_plist	next;

	if (!lst)
		return ;
	while (lst)
	{
		free((*lst)->value);
		(*lst)->value = NULL;
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
	return ;
}
