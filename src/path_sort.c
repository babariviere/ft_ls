/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:28:38 by briviere          #+#    #+#             */
/*   Updated: 2017/11/30 08:42:27 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_sort_subpath(t_path **paths, int (*cmp)(const char *, const char *))
{
	size_t		idx;
	size_t		sub_idx;

	if (paths == 0)
		return ;
	idx = 0;
	while (paths[idx])
	{
		sub_idx = idx + 1;
		while (paths[sub_idx])
		{
			if (cmp(paths[idx]->name, paths[sub_idx]->name) > 0)
				ft_swap_ptr((void**)(paths + idx),
						(void**)(paths + sub_idx));
			sub_idx++;
		}
		idx++;
	}
}

void			ft_sort_subpath_atime(t_path **paths, int rev)
{
	size_t		idx;
	size_t		sub_idx;

	if (paths == 0)
		return ;
	idx = 0;
	while (paths[idx])
	{
		sub_idx = idx + 1;
		while (paths[sub_idx])
		{
			if (!rev && paths[idx]->stat->st_atime >
					paths[sub_idx]->stat->st_atime)
				ft_swap_ptr((void**)(paths + idx),
						(void**)(paths + sub_idx));
			else if (rev && paths[idx]->stat->st_atime <
					paths[sub_idx]->stat->st_atime)
				ft_swap_ptr((void**)(paths + idx),
						(void**)(paths + sub_idx));
			sub_idx++;
		}
		idx++;
	}
}

void			ft_sort_subpath_mtime(t_path **paths, int rev)
{
	size_t		idx;
	size_t		sub_idx;

	if (paths == 0)
		return ;
	idx = 0;
	while (paths[idx])
	{
		sub_idx = idx + 1;
		while (paths[sub_idx])
		{
			if (!rev && paths[idx]->stat->st_mtime >
					paths[sub_idx]->stat->st_mtime)
				ft_swap_ptr((void**)(paths + idx),
						(void**)(paths + sub_idx));
			else if (rev && paths[idx]->stat->st_mtime <
					paths[sub_idx]->stat->st_mtime)
				ft_swap_ptr((void**)(paths + idx),
						(void**)(paths + sub_idx));
			sub_idx++;
		}
		idx++;
	}
}

void			ft_sort_subpath_ctime(t_path **paths, int rev)
{
	size_t		idx;
	size_t		sub_idx;

	if (paths == 0)
		return ;
	idx = 0;
	while (paths[idx])
	{
		sub_idx = idx + 1;
		while (paths[sub_idx])
		{
			if (!rev && paths[idx]->stat->st_ctime >
					paths[sub_idx]->stat->st_ctime)
				ft_swap_ptr((void**)(paths + idx),
						(void**)(paths + sub_idx));
			else if (rev && paths[idx]->stat->st_ctime <
					paths[sub_idx]->stat->st_ctime)
				ft_swap_ptr((void**)(paths + idx),
						(void**)(paths + sub_idx));
			sub_idx++;
		}
		idx++;
	}
}
