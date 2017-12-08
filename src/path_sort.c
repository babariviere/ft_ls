/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:28:38 by briviere          #+#    #+#             */
/*   Updated: 2017/12/08 17:52:32 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dlst		*ft_sort_spath_part(t_dlst *low, t_dlst *high,
		int (*cmp)(const t_path *, const t_path *))
{
	t_path	*p;
	t_dlst	*piv;
	t_dlst	*j;

	p = high->content;
	piv = low->prev;
	j = low;
	while (j != high)
	{
		j = low;
		if (cmp(j->content, p) >= 0)
		{
			piv = (piv == 0 ? low : piv->next);
			ft_swap_ptr((void **)&piv->content, (void **)&j->content);
		}
	}
	piv = (piv == 0 ? low : piv->next);
	ft_swap_ptr((void **)&piv->content, (void **)&j->content);
	return (piv);
}

void		ft_sort_spath_qsort(t_dlst *low, t_dlst *high,
	int (*cmp)(const t_path *, const t_path *))
{
	t_dlst		*part;

	if (low < high)
	{
		part = ft_sort_spath_part(low, high, cmp);
		ft_sort_spath_qsort(low, part->prev, cmp);
		ft_sort_spath_qsort(part->next, high, cmp);
	}
}

void		ft_sort_subpath(t_dlst *files,
		int (*cmp)(const t_path *, const t_path *), int rev)
{
	if (files == 0)
		return ;
	(void)rev;
	ft_sort_spath_qsort(files, ft_dlstget(files, ft_dlstlen(files) - 1), cmp);
	//t_dlst		*begin;
	//t_dlst		*end;

	//if (files == 0)
	//	return ;
	//rev = (rev != 0 ? -1 : 1);
	//begin = files;
	//while (begin && begin->next)
	//{
	//	end = begin->next;
	//	while (end)
	//	{
	//		if ((rev * cmp(begin->content, end->content)) > 0)
	//			ft_swap_ptr(&begin->content, &end->content);
	//		end = end->next;
	//	}
	//	begin = begin->next;
	//}
}

int			ft_path_cmp_size(const t_path *p1, const t_path *p2)
{
	if (p1->fsize == p2->fsize)
		return (ft_strcmp(p1->name, p2->name));
	return (p2->fsize - p1->fsize);
}
