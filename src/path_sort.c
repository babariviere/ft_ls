/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:28:38 by briviere          #+#    #+#             */
/*   Updated: 2017/12/07 16:25:33 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_sort_subpath(t_list *files,
		int (*cmp)(const t_path *, const t_path *), int rev)
{
	t_list		*begin;
	t_list		*end;

	if (files == 0)
		return ;
	begin = files;
	while (begin && begin->next)
	{
		end = begin->next;
		while (end)
		{
			if (!rev && cmp(begin->content, end->content) > 0)
				ft_swap_ptr(&begin->content, &end->content);
			else if (rev && cmp(end->content, begin->content) > 0)
				ft_swap_ptr(&begin->content, &end->content);
			end = end->next;
		}
		begin = begin->next;
	}
}

int			ft_path_cmp_size(const t_path *p1, const t_path *p2)
{
	if (p1->size == p2->size)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->size - p1->size);
}
