/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:28:38 by briviere          #+#    #+#             */
/*   Updated: 2017/12/08 16:03:56 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//int			ft_sort_spath_part(t_list *files, int low, int high,
//		int (*cmp)(const t_path *, const t_path *))
//{
//	t_list	*piv;
//	int		i;
//	int		j;
//
//	i = low - 1;
//	j = high + 1;
//	piv = ft_lstget(files, low);
//	while (1)
//	{
//		i++;
//		while (cmp(piv->content, ft_lstget(files, i)->content) > 0)
//			i++;
//		j--;
//		while (cmp(piv->content, ft_lstget(files, j)->content) < 0)
//			j--;
//		if (i >= j)
//			return (j);
//		ft_swap_ptr((void **)&ft_lstget(files, i)->content, (void **)&ft_lstget(files, j)->content);
//	}
//}
//
//void		ft_sort_spath_qsort(t_list *files, int low, int high,
//	int (*cmp)(const t_path *, const t_path *))
//{
//	int		part;
//
//	if (low < high)
//	{
//		part = ft_sort_spath_part(files, low, high, cmp);
//		ft_sort_spath_qsort(files, low, part, cmp);
//		ft_sort_spath_qsort(files, part + 1, high, cmp);
//	}
//}

void		ft_sort_subpath(t_list *files,
		int (*cmp)(const t_path *, const t_path *), int rev)
{
	//(void)rev;
	//ft_sort_spath_qsort(files, 0, ft_lstlen(files) - 1, cmp);
	//t_list		*begin;
	//t_list		*end;

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
