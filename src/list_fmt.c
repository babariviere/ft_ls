/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fmt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 18:57:53 by briviere          #+#    #+#             */
/*   Updated: 2017/12/05 15:52:51 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_fmt	*path_to_fmt(t_path *path, t_arg opt)
{
	t_fmt		*fmt;
	char		buf[1024];
	size_t		r;

	if ((fmt = ft_init_fmt(8 + (FT_ISLNK(path->stat->st_mode) * 2))) == 0)
		return (0);
	ft_add_fmt_str(fmt, get_permissions(path->stat->st_mode), 0);
	ft_add_fmt_str(fmt, get_xattr_symbol(path->path,
				HAS_FLAG(opt, ARG_FOLLOW_LNK)), 1);
	ft_add_fmt_str(fmt, ft_itoa(path->stat->st_nlink), 1);
	ft_add_fmt_str(fmt, get_pw_name(path->stat->st_uid), 2);
	ft_add_fmt_str(fmt, get_gr_name(path->stat->st_gid), 2 + HAS_FLAG(opt, ARG_HUMAN));
	if (HAS_FLAG(opt, ARG_HUMAN))
		ft_add_fmt_str(fmt, ft_stoa_human(path->stat->st_size, 1), 1);
	else
		ft_add_fmt_str(fmt, ft_itoa(path->stat->st_size), 1);
	if (HAS_FLAG(opt, ARG_CTIME))
		ft_add_fmt_str(fmt, get_file_time(path->stat->st_ctime), 1);
	else if (HAS_FLAG(opt, ARG_ATIME))
		ft_add_fmt_str(fmt, get_file_time(path->stat->st_atime), 1);
	else if (HAS_FLAG(opt, ARG_BTIME))
		ft_add_fmt_str(fmt, get_file_time(path->stat->st_birthtime), 1);
	else
		ft_add_fmt_str(fmt, get_file_time(path->stat->st_mtime), 1);
	ft_add_fmt_str(fmt, ft_strdup(path->name), 1);
	if (FT_ISLNK(path->stat->st_mode))
	{
		ft_add_fmt_str(fmt, ft_strdup("->"), 1);
		r = readlink(path->path, buf, 1024);
		buf[r] = 0;
		ft_add_fmt_str(fmt, ft_strdup(buf), 0);
	}
	return (fmt);
}

static void		print_total_blocks(t_path **path, size_t total_blk,
		size_t tab_len)
{
	char	*tmp;

	if (tab_len == 1 && FT_ISREG(path[0]->stat->st_mode))
		return ;
	ft_putstr("total ");
	tmp = ft_itoa(total_blk);
	ft_putendl(tmp);
	free(tmp);
}

static void		calibrate_list_fmt(t_fmt **fmts)
{
	ft_calibrate_fmt(fmts, 2, -1);
	ft_calibrate_fmt_range(fmts, 3, 4, 0);
	ft_calibrate_fmt(fmts, 5, -1);
}

static void		print_and_free_fmts(t_fmt **fmts, size_t tab_len)
{
	size_t		idx;

	idx = 0;
	while (idx < tab_len)
	{
		ft_print_fmt(fmts[idx]);
		ft_free_fmt(fmts + idx);
		idx++;
		ft_putchar('\n');
	}
	free(fmts);
}

void			print_list_format(t_path **path, t_arg opt)
{
	t_fmt		**fmts;
	size_t		idx;
	size_t		total_blk;
	size_t		tab_len;

	if (path == 0 || *path == 0)
		return ;
	tab_len = ft_tablen(path, sizeof(t_path *));
	if ((fmts = ft_memalloc(sizeof(t_fmt *) * (tab_len + 1))) == 0)
		return ;
	idx = 0;
	total_blk = 0;
	while (idx < tab_len)
	{
		fmts[idx] = path_to_fmt(path[idx], opt);
		total_blk += path[idx]->stat->st_blocks;
		idx++;
	}
	calibrate_list_fmt(fmts);
	print_total_blocks(path, total_blk, tab_len);
	print_and_free_fmts(fmts, tab_len);
}
