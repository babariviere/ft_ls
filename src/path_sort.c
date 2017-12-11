/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:28:38 by briviere          #+#    #+#             */
/*   Updated: 2017/12/11 09:52:53 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_sort_subpath(t_lst *files,
		int (*cmp)(const t_path *, const t_path *), int rev)
{
	t_lst		*begin;
	t_lst		*end;

	if (files == 0)
		return ;
	rev = (rev != 0 ? -1 : 1);
	begin = files;
	while (begin && begin->next)
	{
		end = begin->next;
		while (end)
		{
			if ((rev * cmp(begin->content, end->content)) > 0)
				ft_swap_ptr(&begin->content, &end->content);
			end = end->next;
		}
		begin = begin->next;
	}
}

int			ft_path_cmp_size(const t_path *p1, const t_path *p2)
{
	if (p1->fsize == p2->fsize)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->fsize - p1->fsize);
}
