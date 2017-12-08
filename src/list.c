/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 04:47:06 by briviere          #+#    #+#             */
/*   Updated: 2017/12/08 13:04:45 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_make_sort_paths(t_list *paths, t_arg opt)
{
	int		(*f)(const t_path *, const t_path *);

	f = 0;
	if (opt & ARG_SORT_SIZE)
		f = ft_path_cmp_size;
	else if ((opt & ARG_ATIME) && (opt & ARG_SORT_TIME))
		f = ft_path_cmp_atime;
	else if ((opt & ARG_CTIME) && (opt & ARG_SORT_TIME))
		f = ft_path_cmp_ctime;
	else if ((opt & ARG_MTIME) && (opt & ARG_SORT_TIME))
		f = ft_path_cmp_mtime;
	else if ((opt & ARG_BTIME) && (opt & ARG_SORT_TIME))
		f = ft_path_cmp_btime;
	else if ((opt & ARG_SORT))
		f = ft_path_cmp_name;
	if (f)
		ft_sort_subpath(paths, f, (opt & ARG_REV));
}

void			free_spath(void *content, size_t size)
{
	if (size != sizeof(t_path))
		return ;
	ft_free_path((t_path **)&content);
}

static void		list_files_rec_sub(t_path *path, t_arg opt,
		int follow_lnk, int hidden)
{
	t_list	*spath;

	ft_putchar('\n');
	ft_putstr(path->path);
	ft_putendl(":");
	spath = ft_get_subpath(path->path, follow_lnk, hidden,
			(opt & ARG_SORT) || (opt & ARG_LIST_FMT));
	if (spath == 0)
		return ;
	list_files(spath, opt);
	ft_lstdel(&spath, free_spath);
}

void			list_files_rec(t_list *files, t_arg opt)
{
	int		follow_lnk;
	int		hidden;

	follow_lnk = (opt & ARG_FOLLOW_LNK);
	hidden = (opt & ARG_HIDDEN);
	while (files && files->content_size)
	{
		if (ft_strncmp(((t_path *)files->content)->name, ".", 2) == 0)
		{
			files = files->next;
			continue ;
		}
		if (ft_strncmp(((t_path *)files->content)->name, "..", 3) == 0)
		{
			files = files->next;
			continue ;
		}
		if (!FT_ISDIR(((t_path *)files->content)->mode))
		{
			files = files->next;
			continue ;
		}
		list_files_rec_sub(files->content, opt, follow_lnk, hidden);
		files = files->next;
	}
}

void			list_files(t_list *files, t_arg opt)
{
	t_list	*hld;

	if (files == 0)
		return ;
	ft_make_sort_paths(files, opt);
	if ((opt & ARG_LIST_FMT))
		print_list_format(files, opt);
	else if ((opt & ARG_ONE_ENT))
	{
		hld = files;
		while (hld && hld->content_size)
		{
			ft_putendl(((t_path *)hld->content)->name);
			hld = hld->next;
		}
	}
	if ((opt & ARG_REC))
		list_files_rec(files, opt);
}
