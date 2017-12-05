/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 08:28:38 by briviere          #+#    #+#             */
/*   Updated: 2017/12/05 16:51:32 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_sort_subpath(t_path **paths,
		int (*cmp)(const char *, const char *))
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

void			ft_swap_if_not_gr(t_path **path1, t_path **path2,
		t_arg opt, int rev)
{
	int		res;

	res = (rev ? ft_strcmp_rev((*path1)->name, (*path2)->name) :
			ft_strcmp((*path1)->name, (*path2)->name));
	if (HAS_FLAG(opt, ARG_ATIME) &&
		(*path1)->stat->st_atime == (*path2)->stat->st_atime &&
		res <= 0)
		return ;
	else if (HAS_FLAG(opt, ARG_CTIME) &&
		(*path1)->stat->st_ctime == (*path2)->stat->st_ctime &&
		res <= 0)
		return ;
	else if (HAS_FLAG(opt, ARG_MTIME) &&
		(*path1)->stat->st_mtime == (*path2)->stat->st_mtime &&
		res <= 0)
		return ;
	else if (HAS_FLAG(opt, ARG_BTIME) &&
		(*path1)->stat->st_birthtime == (*path2)->stat->st_birthtime &&
		res <= 0)
		return ;
	ft_swap_ptr((void **)path1, (void **)path2);
}

void			ft_sort_subpath_atime(t_path **paths, int rev)
{
	size_t		idx;
	size_t		sub_idx;

	if (paths == 0)
		return ;
	idx = 0;
	while (paths[idx] && paths[idx + 1])
	{
		sub_idx = idx + 1;
		while (paths[sub_idx])
		{
			if (!rev && paths[idx]->stat->st_atime <=
					paths[sub_idx]->stat->st_atime)
				ft_swap_if_not_gr((paths + idx),
						(paths + sub_idx), ARG_ATIME, rev);
			else if (rev && paths[idx]->stat->st_atime >=
					paths[sub_idx]->stat->st_atime)
				ft_swap_if_not_gr((paths + idx),
						(paths + sub_idx), ARG_ATIME, rev);
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
	while (paths[idx] && paths[idx + 1])
	{
		sub_idx = idx + 1;
		while (paths[sub_idx])
		{
			if (!rev && paths[idx]->stat->st_mtime <=
					paths[sub_idx]->stat->st_mtime)
				ft_swap_if_not_gr((paths + idx),
						(paths + sub_idx), ARG_MTIME, rev);
			else if (rev && paths[idx]->stat->st_mtime >=
					paths[sub_idx]->stat->st_mtime)
				ft_swap_if_not_gr((paths + idx),
						(paths + sub_idx), ARG_MTIME, rev);
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
	while (paths[idx] && paths[idx + 1])
	{
		sub_idx = idx + 1;
		while (paths[sub_idx])
		{
			if (!rev && paths[idx]->stat->st_ctime <=
					paths[sub_idx]->stat->st_ctime)
				ft_swap_if_not_gr((paths + idx),
						(paths + sub_idx), ARG_CTIME, rev);
			else if (rev && paths[idx]->stat->st_ctime >=
					paths[sub_idx]->stat->st_ctime)
				ft_swap_if_not_gr((paths + idx),
						(paths + sub_idx), ARG_CTIME, rev);
			sub_idx++;
		}
		idx++;
	}
}
