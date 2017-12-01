/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fmt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 18:57:53 by briviere          #+#    #+#             */
/*   Updated: 2017/12/01 01:57:53 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_fmt	*path_to_fmt(t_path *path, int human)
{
	t_fmt		*fmt;
	char			buf[1024];
	size_t			r;

	if ((fmt = ft_init_fmt(8 +
					(FT_ISLNK(path->stat->st_mode) * 2))) == 0)
		return (0);
	ft_add_fmt_str(fmt, get_permissions(path->stat->st_mode), 0);
	ft_add_fmt_str(fmt, ft_strdup("a"), 1); // TODO: extended attributes
	ft_add_fmt_str(fmt, ft_itoa(path->stat->st_nlink), 1);
	ft_add_fmt_str(fmt, get_pw_name(path->stat->st_uid), 2);
	ft_add_fmt_str(fmt, get_gr_name(path->stat->st_gid), 2 + human);
	if (human)
		ft_add_fmt_str(fmt, ft_stoa_human(path->stat->st_size, 1), 1);
	else
		ft_add_fmt_str(fmt, ft_itoa(path->stat->st_size), 1);
	ft_add_fmt_str(fmt, get_file_time(path->stat->st_mtimespec), 1);
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

void				print_list_format(t_path **path, t_arg_opt *opt)
{
	t_fmt		**fmts;
	size_t		idx;

	if (path == 0 || *path == 0)
		return ;
	if ((fmts = ft_memalloc(sizeof(t_fmt *) *
					(ft_tablen(path, sizeof(t_path *)) + 1))) == 0)
		return ;
	idx = 0;
	while (path[idx])
	{
		fmts[idx] = path_to_fmt(path[idx], opt->human);
		idx++;
	}
	ft_calibrate_fmt_range(fmts, 2, 5, -1);
	idx = 0;
	while (fmts[idx])
	{
		ft_print_fmt(fmts[idx]);
		ft_free_fmt(fmts + idx);
		idx++;
		ft_putchar('\n');
	}
	free(fmts);
}
