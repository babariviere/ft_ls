/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:41:22 by briviere          #+#    #+#             */
/*   Updated: 2017/12/08 17:10:53 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		list_dir(char *dir, t_arg arg)
{
	t_path	*path;
	t_dlst	*spath;

	path = ft_init_path(0, dir, -1);
	ft_path_readstat(path, (arg & ARG_FOLLOW_LNK));
	if (path == 0)
	{
		print_last_err(dir);
		return ;
	}
	if (!FT_ISDIR(path->mode))
		spath = ft_dlstnew_mv(ft_init_path(0, dir, DT_REG), sizeof(t_path));
	else
		spath = ft_get_subpath(path->path, (arg & ARG_FOLLOW_LNK),
				(arg & ARG_HIDDEN),
				(arg & ARG_LIST_FMT) || (arg & ARG_SORT));
	if (spath == 0)
	{
		print_last_err(dir);
		return ;
	}
	if (spath->content != 0)
		list_files(spath, arg);
	ft_dlstdel(&spath, free_spath);
	ft_free_path(&path);
}

int			path_is_file(t_dlst *elem)
{
	t_path		*p;

	p = elem->content;
	return (!FT_ISDIR(p->mode));
}

void		print_files(t_dlst *list, t_arg arg)
{
	t_dlst		*files;

	files = ft_dlstfilter(list, path_is_file);
	if (!(arg & ARG_SORT_TIME) && (arg & ARG_SORT))
		ft_make_sort_paths(files, arg);
	list_files(files, arg);
	ft_dlstdel(&files, free_spath);
}

void		print_dirs(t_dlst *paths, t_arg arg, int print, int has_file)
{
	t_dlst		*path;

	path = paths;
	while (path)
	{
		if (!FT_ISDIR(((t_path *)path->content)->mode))
		{
			path = path->next;
			continue ;
		}
		if (print)
		{
			if (path != paths || has_file)
				ft_putchar('\n');
			ft_putstr(((t_path *)path->content)->name);
			ft_putendl(":");
		}
		list_dir(((t_path *)path->content)->name, arg);
		path = path->next;
	}
}

void		list_av(char **av, t_arg arg)
{
	t_dlst	*paths;
	t_dlst	*path;
	size_t	idx;
	int		print;
	int		has_file;

	if (*av == 0)
		list_dir(".", arg);
	print = av[0] && av[1];
	idx = 0;
	has_file = 0;
	paths = 0;
	while (av[idx])
	{
		path = ft_dlstnew_mv(ft_init_path(0, av[idx++], -1), sizeof(t_path));
		if (ft_path_readstat(path->content, (arg & ARG_FOLLOW_LNK)) == 0)
			return ;
		if (path->content && !FT_ISDIR(((t_path *)path->content)->mode))
			has_file = 1;
		if (path)
			ft_dlstpush(&paths, path);
	}
	print_files(paths, arg);
	if (!(arg & ARG_SORT_TIME) && (arg & ARG_SORT))
		ft_make_sort_paths(paths, arg);
	print_dirs(paths, arg, print, has_file);
	free(paths);
}

int			check_empty(char **av)
{
	size_t		sidx;

	sidx = 0;
	while (av[sidx])
	{
		if (av[sidx++][0] == 0)
		{
			ft_putstr_fd("ls: fts_open: No such file or directory\n", 2);
			return (0);
		}
	}
	return (1);
}

int			main(int ac, char **av)
{
	t_arg		arg;
	int			idx;

	arg = ARG_ONE_ENT | ARG_SORT;
	idx = 1;
	while (idx < ac)
	{
		if (av[idx][0] == '-' && av[idx][1] == '-' && av[idx][2] == 0)
		{
			idx++;
			break ;
		}
		else if (av[idx][0] == '-' && av[idx][1] != 0)
		{
			if (parse_arg(&arg, av[idx++]) == 0)
				return (usage(1));
		}
		else
			break ;
	}
	if (check_empty(av + idx) == 0)
		return (1);
	list_av(av + idx, arg);
	return (0);
}
