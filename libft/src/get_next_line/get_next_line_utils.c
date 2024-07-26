/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbekheir <mbekheir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:47:02 by mbekheir          #+#    #+#             */
/*   Updated: 2024/07/26 16:34:43 by mbekheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_new_line(t_list *lst)
{
	t_list	*current;
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

t_list	*get_last_node(t_list *lst)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	generate_line(t_list *lst, char **line)
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
		return (free_list(lst));
}

void	free_list(t_list *lst)
{
	t_list	*tmp;
	t_list	*next;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		ft_free(tmp->value);
		tmp->value = NULL;
		next = tmp->next;
		ft_free(tmp);
		tmp = next;
	}
	tmp = NULL;
	return ;
}
