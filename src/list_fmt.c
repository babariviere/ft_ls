/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fmt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 18:57:53 by briviere          #+#    #+#             */
/*   Updated: 2017/12/08 13:26:20 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		path_to_fmt_sub(t_path *path, t_arg opt, t_fmt *fmt)
{
	if ((opt & ARG_HUMAN))
		ft_add_fmt_str(fmt, ft_stoa_human(path->size, 1), 1);
	else
		ft_add_fmt_str(fmt, ft_itoa(path->size), 1);
	if ((opt & ARG_CTIME))
		ft_add_fmt_str(fmt, get_file_time(path->ctime), 1);
	else if ((opt & ARG_ATIME))
		ft_add_fmt_str(fmt, get_file_time(path->atime), 1);
	else if ((opt & ARG_BTIME))
		ft_add_fmt_str(fmt, get_file_time(path->btime), 1);
	else
		ft_add_fmt_str(fmt, get_file_time(path->mtime), 1);
}

static t_fmt	*path_to_fmt(t_path *path, t_arg opt)
{
	t_fmt		*fmt;
	char		buf[1024];
	size_t		r;

	if ((fmt = ft_init_fmt(8 + (FT_ISLNK(path->mode) * 2))) == 0)
		return (0);
	ft_add_fmt_str(fmt, get_permissions(path->mode), 0);
	ft_add_fmt_str(fmt, get_xattr_symbol(path->path,
				(opt & ARG_FOLLOW_LNK)), 1);
	ft_add_fmt_str(fmt, ft_itoa(path->nlink), 1);
	ft_add_fmt_str(fmt, get_pw_name(path->uid), 2);
	ft_add_fmt_str(fmt, get_gr_name(path->gid), 2 +
			(opt & ARG_HUMAN));
	path_to_fmt_sub(path, opt, fmt);
	ft_add_fmt_str(fmt, ft_strdup(path->name), 1);
	if (FT_ISLNK(path->mode))
	{
		ft_add_fmt_str(fmt, ft_strdup("->"), 1);
		r = readlink(path->path, buf, 1024);
		buf[r] = 0;
		ft_add_fmt_str(fmt, ft_strdup(buf), 0);
	}
	return (fmt);
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

void			print_list_format(t_list *files, t_arg opt)
{
	t_fmt		**fmts;
	t_list		*hld;
	size_t		idx;
	size_t		total_blk;
	size_t		tab_len;

	if (files == 0 || files->content_size == 0)
		return ;
	tab_len = ft_lstlen(files);
	if ((fmts = malloc(sizeof(t_fmt *) * (tab_len + 1))) == 0)
		return ;
	idx = 0;
	total_blk = 0;
	hld = files;
	while (hld && hld->content_size)
	{
		fmts[idx++] = path_to_fmt(hld->content, opt);
		total_blk += ((t_path *)hld->content)->blocks;
		hld = hld->next;
	}
	fmts[idx] = 0;
	calibrate_list_fmt(fmts);
	print_total_blocks(files->content, total_blk, tab_len);
	print_and_free_fmts(fmts, tab_len);
}
