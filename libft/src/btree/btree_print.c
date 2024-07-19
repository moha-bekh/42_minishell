/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moha <moha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:28:00 by moha              #+#    #+#             */
/*   Updated: 2024/07/08 20:01:26 by moha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_ptr(t_btree *btree, bool prefix)
{
	if (btree->parent)
		ft_printf("[%p] -> [%p]\n", btree->parent->value, btree->value);
	else
		ft_printf("[%p]\n", btree->value);
	if (prefix)
	{
		if (btree->left)
			btree_ptr(btree->left, prefix);
		if (btree->right)
			btree_ptr(btree->right, prefix);
	}
	else
	{
		if (btree->right)
			btree_ptr(btree->right, prefix);
		if (btree->left)
			btree_ptr(btree->left, prefix);
	}
	return ;
}

void	btree_int(t_btree *btree, bool prefix, int tab)
{
	print_tab(tab);
	print_parent(btree);
	if (prefix)
	{
		if (btree->left)
			btree_int(btree->left, prefix, tab + 1);
		if (btree->right)
			btree_int(btree->right, prefix, tab + 1);
	}
	else
	{
		if (btree->right)
			btree_int(btree->right, prefix, tab + 1);
		if (btree->left)
			btree_int(btree->left, prefix, tab + 1);
	}
	return ;
}

void	btree_str(t_btree *btree, bool prefix)
{
	if (btree->parent)
		ft_printf("[%s] -> [%s]\n", *(char *)btree->parent->value,
			*(char *)btree->value);
	else
		ft_printf("[%s]\n", *(char *)btree->value);
	if (prefix)
	{
		if (btree->left)
			btree_str(btree->left, prefix);
		if (btree->right)
			btree_str(btree->right, prefix);
	}
	else
	{
		if (btree->right)
			btree_str(btree->right, prefix);
		if (btree->left)
			btree_str(btree->left, prefix);
	}
	return ;
}

void	btree_char(t_btree *btree, bool prefix)
{
	if (btree->parent)
		ft_printf("[%c] -> [%c]\n", *(char *)btree->parent->value,
			*(char *)btree->value);
	else
		ft_printf("[%c]\n", *(char *)btree->value);
	if (prefix)
	{
		if (btree->left)
			btree_char(btree->left, prefix);
		if (btree->right)
			btree_char(btree->right, prefix);
	}
	else
	{
		if (btree->right)
			btree_char(btree->right, prefix);
		if (btree->left)
			btree_char(btree->left, prefix);
	}
	return ;
}

void	btree_print(t_btree *btree, void (*in_type)(t_btree *btree, bool prefix,
			int tab), bool prefix)
{
	if (!btree)
		return ;
	return (in_type(btree, prefix, 0));
}
