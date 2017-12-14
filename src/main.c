/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:41:22 by briviere          #+#    #+#             */
/*   Updated: 2017/12/12 16:30:46 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		list_dir(char *dir, t_arg arg)
{
	t_path	*path;
	t_lst	*spath;

	path = ft_init_path(0, dir, -1);
	ft_path_readstat(path, 1);
	if (path == 0)
	{
		print_last_err(dir);
		return ;
	}
	if (!FT_ISDIR(path->mode))
		spath = ft_lstnew_mv(ft_init_path(0, dir, DT_REG), sizeof(t_path));
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
	ft_lstdel(&spath, free_spath);
	ft_free_path(&path);
}

void		list_av_sub(t_lst *paths, t_arg arg, int print, int has_file)
{
	print_files(paths, arg);
	if (!(arg & ARG_SORT_TIME) && (arg & ARG_SORT))
		ft_make_sort_paths(paths, arg);
	print_dirs(paths, arg, print, has_file);
}

void		list_av(char **av, t_arg arg)
{
	t_lst	*paths;
	t_lst	*path;
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
		path = ft_lstnew_mv(ft_init_path(0, av[idx++], -1), sizeof(t_path));
		if (ft_path_readstat(path->content, 1) == 0)
			return ;
		if (path->content && !FT_ISDIR(((t_path *)path->content)->mode))
			has_file = 1;
		if (path)
			ft_lstpush(&paths, path);
	}
	list_av_sub(paths, arg, print, has_file);
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
