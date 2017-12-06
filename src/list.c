/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 04:47:06 by briviere          #+#    #+#             */
/*   Updated: 2017/12/06 16:32:45 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_make_sort_paths(t_path **path, t_arg opt)
{
	if (HAS_FLAG(opt, ARG_SORT_SIZE))
		ft_sort_subpath_size(path, HAS_FLAG(opt, ARG_REV));
	else if (HAS_FLAG(opt, ARG_ATIME) && HAS_FLAG(opt, ARG_SORT_TIME))
		ft_sort_subpath_atime(path, HAS_FLAG(opt, ARG_REV));
	else if (HAS_FLAG(opt, ARG_CTIME) && HAS_FLAG(opt, ARG_SORT_TIME))
		ft_sort_subpath_ctime(path, HAS_FLAG(opt, ARG_REV));
	else if (HAS_FLAG(opt, ARG_MTIME) && HAS_FLAG(opt, ARG_SORT_TIME))
		ft_sort_subpath_mtime(path, HAS_FLAG(opt, ARG_REV));
	else if (HAS_FLAG(opt, ARG_BTIME) && HAS_FLAG(opt, ARG_SORT_TIME))
		ft_sort_subpath_btime(path, HAS_FLAG(opt, ARG_REV));
	else if (HAS_FLAG(opt, ARG_SORT))
		ft_sort_subpath(path, (HAS_FLAG(opt, ARG_REV) ?
					ft_strcmp_rev : ft_strcmp));
}

static void		free_spath(t_path **spath)
{
	size_t	idx;

	idx = 0;
	while (spath[idx])
	{
		ft_free_path(spath + idx);
		idx++;
	}
}

static void		list_files_rec_sub(t_path *path, t_arg opt,
		int follow_lnk, int hidden)
{
	t_path	**spath;

	spath = ft_get_subpath(path->path, follow_lnk, hidden);
	ft_putchar('\n');
	ft_putstr(path->path);
	ft_putendl(":");
	if (spath == 0)
	{
		perror("ls: ");
		return ;
	}
	list_files(spath, opt);
	free_spath(spath);
	free(spath);
}

void			list_files_rec(t_path **path, t_arg opt)
{
	int		idx;
	int		follow_lnk;
	int		hidden;

	idx = -1;
	follow_lnk = HAS_FLAG(opt, ARG_FOLLOW_LNK);
	hidden = HAS_FLAG(opt, ARG_HIDDEN);
	while (path[++idx])
	{
		if (ft_strequ(path[idx]->name, ".") ||
				ft_strequ(path[idx]->name, ".."))
			continue ;
		if (!FT_ISDIR(path[idx]->stat->st_mode))
			continue ;
		list_files_rec_sub(path[idx], opt, follow_lnk, hidden);
	}
}

void			list_files(t_path **path, t_arg opt)
{
	size_t	idx;

	if (path == 0)
		return ;
	ft_make_sort_paths(path, opt);
	if (HAS_FLAG(opt, ARG_LIST_FMT))
		print_list_format(path, opt);
	else if (HAS_FLAG(opt, ARG_ONE_ENT))
	{
		idx = 0;
		while (path[idx])
			ft_putendl(path[idx++]->name);
	}
	if (HAS_FLAG(opt, ARG_REC))
		list_files_rec(path, opt);
}
