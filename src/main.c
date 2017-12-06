/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briviere <briviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:41:22 by briviere          #+#    #+#             */
/*   Updated: 2017/12/06 12:34:41 by briviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		list_dir(char *dir, t_arg arg)
{
	t_path	*path;
	t_path	**spath;
	int		idx;

	path = ft_init_path(0, dir, HAS_FLAG(arg, ARG_FOLLOW_LNK));
	if (path == 0)
	{
		perror(dir);
		return ;
	}
	if (!FT_ISDIR(path->fstat->st_mode))
	{
		spath = ft_memalloc(sizeof(t_path *) * 2);
		spath[0] = ft_init_path(0, dir, HAS_FLAG(arg, ARG_FOLLOW_LNK));
		spath[1] = 0;
	}
	else
		spath = ft_get_subpath(path->path, HAS_FLAG(arg, ARG_FOLLOW_LNK),
				HAS_FLAG(arg, ARG_HIDDEN));
	if (spath == 0)
	{
		ft_putstr("ls: ");
		perror(dir);
		return ;
	}
	list_files(spath, arg);
	idx = 0;
	while (spath[idx])
	{
		ft_free_path(spath + idx);
		idx++;
	}
	free(spath);
	ft_free_path(&path);
}

void		print_files(t_path **paths, t_arg arg)
{
	t_path		**files;
	size_t		idx;
	size_t		sidx;
	
	idx = 0;
	sidx = 0;
	while (paths[idx])
	{
		if (!FT_ISDIR(paths[idx]->fstat->st_mode))
		{
			ft_swap_ptr((void **)(paths + idx), (void **)(paths + sidx));
			sidx++;
		}
		idx++;
	}
	files = ft_memalloc(sizeof(t_path *) * (sidx + 1));
	ft_memcpy(files, paths, sizeof(t_path *) * sidx);
	files[sidx] = 0;
	list_files(files, arg);
	free(files);
}


void		list_av(char **av, t_arg arg)
{
	t_path	**paths;
	size_t	idx;
	size_t	sidx;
	int		print;
	int		has_file;

	if (*av == 0)
		list_dir(".", arg);
	if ((paths = ft_memalloc(sizeof(t_path *) *
					(ft_tablen(av, sizeof(char *)) + 1))) == 0)
		return ;
	print = av[0] && av[1];
	idx = 0;
	sidx = 0;
	has_file = 0;
	while (av[idx])
	{
		paths[sidx] = ft_init_path(0, av[idx], HAS_FLAG(arg, ARG_FOLLOW_LNK));
		if (paths[sidx] && !FT_ISDIR(paths[sidx]->fstat->st_mode))
			has_file = 1;
		if (paths[sidx])
			sidx++;
		idx++;
	}
	if (!HAS_FLAG(arg, ARG_SORT_TIME) && HAS_FLAG(arg, ARG_SORT))
		ft_make_sort_paths(paths, arg);
	print_files(paths, arg);
	if (!HAS_FLAG(arg, ARG_SORT_TIME) && HAS_FLAG(arg, ARG_SORT))
		ft_make_sort_paths(paths, arg);
	idx = 0;
	while (paths[idx])
	{
		if (!FT_ISDIR(paths[idx]->fstat->st_mode))
		{
			idx++;
			continue ;
		}
		if (print)
		{
			if (idx > 0 || has_file)
				ft_putchar('\n');
			ft_putstr(paths[idx]->name);
			ft_putendl(":");
		}
		list_dir(paths[idx]->name, arg);
		ft_free_path(paths + idx);
		idx++;
	}
	free(paths);
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
	list_av(av + idx, arg);
	return (0);
}
